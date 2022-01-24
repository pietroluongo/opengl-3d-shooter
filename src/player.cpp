#include "../include/player.h"
#include "../include/globalCtx.h"
#include <cmath>
#include <string>
#include <vector>

extern GlobalCtx* context;

float limitArmMovement(float angle);

Player::Player(GLfloat x, GLfloat y, GLfloat size) : Character(x, y, size) {
    this->armPosition = 0.2 * size;
    this->armWidth = 0.04 * size;
    this->armHeight = 0.4 * size;
}

Player::~Player() { delete (this->collider); }

void Player::draw() {
    glfvec2 position = this->getPosition();
    glPushMatrix();
    glTranslatef(position.x, position.y, 0.0f);
    glColor3f(0.0f, 1.0f, 1.0f);
    this->drawChest();
    glColor3f(1.0f, 1.0f, 1.0f);
    this->drawHead();
    this->drawLegs();
    glColor3f(1.0f, 0.0f, 0.0f);
    this->drawArm();

    if (context->shouldObjectsDrawCoordinateSystem) {
        this->drawAxis();
    }
    glPopMatrix();

    if (context->shouldObjectsDrawColliders)
        this->collider->draw();
}

void Player::idle() {
    this->isRequestingMove = false;
    if (this->getCollisionArr()[3]) {
        this->isGrounded = true;
    }
    this->Object::idle();
    this->handleMovementKeys();
    this->updateAnimState();
    this->handleJump();
    this->updateArmAngle();
}

void Player::handleMovementKeys() {
    if (context->isKeyPressed('D') || context->isKeyPressed('d')) {
        this->isRequestingMove = true;
        this->moveX(20);
    }
    if (context->isKeyPressed('A') || context->isKeyPressed('a')) {
        this->isRequestingMove = true;
        this->moveX(-20);
    }

    if (context->isKeyPressed('w') || context->isKeyPressed('W')) {
        this->isRequestingJump = true;
    } else {
        this->isRequestingJump = false;
    }

    if (context->isKeyPressed('s') || context->isKeyPressed('S')) {
        this->moveY(20);
    }

    if (context->isKeyPressed(' ')) {
    }
}

float limitArmMovement(float angle) {
    if (angle > -45 && angle < 0) {
        return -45;
    } else if (angle < -135 && angle > -180) {
        return -135;
    } else if (angle < -180 && angle > -225) {
        return -225;
    } else if (angle < 45 && angle > 0) {
        return 45;
    }
    return angle;
}

void Player::updateArmAngle() {
    glm::fvec2 mousePos = context->getWorldSpaceMousePos();
    glfvec2 position = this->getPosition();
    this->armAngle =
        atan2(mousePos.y - position.y, mousePos.x - position.x) * 180 / M_PI -
        90;
    this->armAngle = limitArmMovement(this->armAngle);
    if ((this->armAngle >= 45 && this->armAngle <= 90) ||
        this->armAngle <= -225) {
        this->setHeading(LEFT);
    } else {
        this->setHeading(RIGHT);
    }
}

void Player::handleJump() {
    if (this->isRequestingJump) {
        this->wasRequestingJump = true;
    }
    if (this->isGrounded) {
        jumpTime = 0;
        this->wasRequestingJump = false;
        shouldIncreaseHeight = true;
        this->setIsAffectedByGravity(false);
    }
    if (this->jumpTime >= 2) {
        this->setIsAffectedByGravity(true);
    }
    if (!this->isGrounded && !this->isRequestingJump) {
        this->setIsAffectedByGravity(true);
    }
    if (this->wasRequestingJump && !this->isRequestingJump) {
        shouldIncreaseHeight = false;
    }
    if (this->isRequestingJump && this->jumpTime < 2 && shouldIncreaseHeight) {
        this->moveY(-10);
    }
    this->jumpTime += context->getDeltaTime();
}

void Player::shoot() {
    glfvec2 position = this->getPosition();
    context->getGameRef()->createProjectile(
        position.x + (this->armHeight * sin(-this->armAngle * M_PI / 180)),
        position.y + (this->armHeight * cos(this->armAngle * M_PI / 180)), 0.5,
        (90 + this->armAngle) * M_PI / 180);
}

void Player::updateAnimState() {
    if (this->isGrounded) {
        if (this->isRequestingMove) {
            this->currentAnimState = AnimState::WALKING;
        } else {

            this->currentAnimState = AnimState::IDLE;
        }
    } else {
        this->currentAnimState = AnimState::JUMPING;
    }
}

void Player::kill() { context->getGameRef()->setState(GameState::OVER); }