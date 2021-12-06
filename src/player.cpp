#include "../include/player.h"

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