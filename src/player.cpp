#include "../include/player.h"
#include "../include/globalCtx.h"

extern GlobalCtx* context;

Player::Player(GLfloat x, GLfloat y) {
    this->position.x = x;
    this->position.y = y;
}

Player::Player() {}

void Player::draw() {
    glPushMatrix();
    glTranslatef(this->position.x, this->position.y, 0.0f);
    glBegin(GL_QUADS);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.0f, 0.1f);
    glVertex2f(0.1f, 0.1f);
    glVertex2f(0.1f, 0.0f);
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
