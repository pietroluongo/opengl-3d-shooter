#include "../include/player.h"
#include "../include/globalCtx.h"
#include <cmath>
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
    this->handleMovementKeys();
    this->Object::idle();
    this->updateArmAngle();

    if (this->isGrounded)
        this->isJumping = false;

    this->updateAnimState();
}

void Player::handleMovementKeys() {
    if (context->isKeyPressed('D') || context->isKeyPressed('d')) {
        this->moveX(20);
        this->currentState = AnimState::WALKING;
    }
    if (context->isKeyPressed('A') || context->isKeyPressed('a')) {
        this->moveX(-20);
        this->currentState = AnimState::WALKING;
    }

    if (context->isKeyPressed('w') || context->isKeyPressed('W')) {
        this->jump();
        // this->moveY(-20);
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

void Player::jump() {
    if (this->isJumping) {
        this->jumpTime += context->getDeltaTime();
        return;
    }
    this->isJumping = true;
}

void Player::shoot() {
    glfvec2 position = this->getPosition();
    context->getGameRef()->createProjectile(
        position.x + (this->armHeight * sin(-this->armAngle * M_PI / 180)),
        position.y + (this->armHeight * cos(this->armAngle * M_PI / 180)), 0.5,
        (90 + this->armAngle) * M_PI / 180);
}

void Player::updateAnimState() {
    this->currentState = AnimState::IDLE;
    // if (context->isKeyPressed('D') || context->isKeyPressed('d')) {
    //     this->currentState = AnimState::WALKING;
    // }
}
