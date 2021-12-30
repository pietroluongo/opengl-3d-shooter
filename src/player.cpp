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
    glBegin(GL_QUADS);
    glColor3f(0.0f, this->size, 0.0f);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.0f, this->size);
    glVertex2f(this->size, this->size);
    glVertex2f(this->size, 0.0f);
    glEnd();
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