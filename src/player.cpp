#include "../include/player.h"
#include "../include/globalCtx.h"
#include <cmath>

extern GlobalCtx* context;

static float CHEST_PROPORTION = 0.5f;
static float HEAD_PROPORTION = 0.1f;
static float LEGS_PROPORTION = 0.4f;

Player::Player(GLfloat x, GLfloat y, GLfloat size) : Character(x, y, size) {}

Player::~Player() {}

void Player::draw() {
    glPushMatrix();
    glTranslatef(this->position.x, this->position.y, 0.0f);
    glColor3f(0.0f, 1.0f, 1.0f);
    this->drawChest();
    glColor3f(1.0f, 0.0f, 0.0f);
    this->drawArm();
    if (context->shouldObjectsDrawCoordinateSystem) {
        this->drawAxis();
    }
    glPopMatrix();
}
void Player::idle() {
    this->updateArmAngle();
    this->handleMovementKeys();
}

void Player::handleMovementKeys() {
    if (context->isKeyPressed('D') || context->isKeyPressed('d')) {
        this->moveX(50);
    }
    if (context->isKeyPressed('A') || context->isKeyPressed('a')) {
        this->moveX(-50);
    }

    if (context->isKeyPressed('w') || context->isKeyPressed('W')) {
        this->moveY(-50);
    }

    if (context->isKeyPressed('s') || context->isKeyPressed('S')) {
        this->moveY(50);
    }
}

void Player::drawChest() {
    glBegin(GL_QUADS);
    glVertex2f(-this->size / 4, -this->size / 2);
    glVertex2f(this->size / 4, -this->size / 2);
    glVertex2f(this->size / 4, this->size / 2);
    glVertex2f(-this->size / 4, this->size / 2);
    glEnd();
}

void Player::drawArm() {
    glPushMatrix();
    glRotatef(this->armAngle, 0.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);
    {
        glVertex2f(-this->armWidth, 0);
        glVertex2f(this->armWidth, 0);
        glVertex2f(this->armWidth, this->armHeight);
        glVertex2f(-this->armWidth, this->armHeight);
    }
    glEnd();
    glPopMatrix();
}

void Player::updateArmAngle() {
    glm::fvec2 mousePos = context->getWorldSpaceMousePos();
    this->armAngle =
        atan2(mousePos.y - this->position.y, mousePos.x - this->position.x) *
            180 / M_PI -
        90;
    if (this->armAngle > -45 && this->armAngle < 0) {
        this->armAngle = -45;
    } else if (this->armAngle < -135 && this->armAngle > -180) {
        this->armAngle = -135;
    } else if (this->armAngle < -180 && this->armAngle > -225) {
        this->armAngle = -225;
    } else if (this->armAngle < 45 && this->armAngle > 0) {
        this->armAngle = 45;
    }
    glBegin(GL_LINES);
    glVertex2f(this->position.x, this->position.y);
    glVertex2f(mousePos.x, mousePos.y);
    glEnd();
}