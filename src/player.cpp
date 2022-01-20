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
    glPushMatrix();
    glTranslatef(this->position.x, this->position.y, 0.0f);
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
    }
    if (context->isKeyPressed('A') || context->isKeyPressed('a')) {
        this->moveX(-20);
    }

    if (context->isKeyPressed('w') || context->isKeyPressed('W')) {
        this->jump();
    }

    if (context->isKeyPressed('s') || context->isKeyPressed('S')) {
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
    this->armAngle =
        atan2(mousePos.y - this->position.y, mousePos.x - this->position.x) *
            180 / M_PI -
        90;
    this->armAngle = limitArmMovement(this->armAngle);
}

void Player::jump() {
    if (this->isJumping) {
        return;
    }
    this->isJumping = true;
}

void Player::shoot() {
    context->getGameRef()->createProjectile(
        this->position.x +
            (this->armHeight * sin(-this->armAngle * M_PI / 180)),
        this->position.y + (this->armHeight * cos(this->armAngle * M_PI / 180)),
        0.5, (90 + this->armAngle) * M_PI / 180);
}

void Player::updateAnimState() { this->currentState = AnimState::IDLE; }
