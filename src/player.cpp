#include "../include/player.h"
#include "../include/globalCtx.h"

extern GlobalCtx* context;

void handleMovementKeys();

Player::Player(GLfloat x, GLfloat y, GLfloat size) {
    this->position.x = x;
    this->position.y = y;
    this->size = size;
}

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

glfvec2 Player::getPosition() { return this->position; }

void Player::moveX(double amount) {
    this->position.x += (amount * context->getDeltaTime());
}

void Player::moveY(double amount) {
    this->position.y += (amount * context->getDeltaTime());
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

void Player::idle() { this->handleMovementKeys(); }