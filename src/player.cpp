#include "../include/player.h"
#include "../include/globalCtx.h"

extern GlobalCtx* context;

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
    // glBegin(GL_LINES);
    // {
    //     glVertex2f(0.0f, 0.0f);
    //     glVertex2f(correctedMousePos.x, correctedMousePos.y);
    //     printf("%f %f\n", correctedMousePos.x, correctedMousePos.y);
    // }
    // glEnd();
}