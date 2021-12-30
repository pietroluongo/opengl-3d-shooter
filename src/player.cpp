#include "../include/player.h"
#include "../include/globalCtx.h"

extern GlobalCtx* context;

Player::Player(GLfloat x, GLfloat y, GLfloat size) : Character(x, y) {
    this->setSize(size);
}

Player::~Player() {}

void Player::draw() {
    glPushMatrix();
    glTranslatef(this->position.x, this->position.y, 0.0f);
    glColor3f(0.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(-this->size / 2, -this->size / 2);
    glVertex2f(this->size / 2, -this->size / 2);
    glVertex2f(this->size / 2, this->size / 2);
    glVertex2f(-this->size / 2, this->size / 2);
    glEnd();
    if (context->shouldObjectsDrawCoordinateSystem) {
        this->drawAxis();
    }
    glPopMatrix();
}
void Player::idle() { this->handleMovementKeys(); }

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