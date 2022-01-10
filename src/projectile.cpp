#include "../include/projectile.h"

Projectile::Projectile(float x, float y, float size) : Object(x, y) {
    this->collider =
        new Collider(x, y, size, size, this, pivotPosition::CENTER);
    this->size = size;
}

void Projectile::draw() {
    glPushMatrix();
    glTranslatef(this->position.x, this->position.y, 0);
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    for (int i = 0; i < 360; i++) {
        glVertex2f(cos(i) * this->size, sin(i) * this->size);
    }
    glEnd();
    glPopMatrix();
}

void Projectile::idle() { this->collider->idle(); }

void Projectile::moveX(double) {}
void Projectile::moveY(double) {}

void Projectile::setPosition(glfvec2 position) {
    this->Object::setPosition(position);
}

void Projectile::setPosition(GLfloat x, GLfloat y) {
    this->Object::setPosition(x, y);
}