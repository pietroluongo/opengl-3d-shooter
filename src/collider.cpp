#include "../include/collider.h"
#include <cstdio>

Collider::Collider(float x, float y, float w, float h, Object* owner,
                   pivotPosition pivot) {
    this->position = glfvec2(x, y);
    this->width = w;
    this->height = h;
    this->pivot = pivot;
    this->owner = owner;
}

void Collider::draw() {
    glPushMatrix();
    glTranslatef(this->position.x, this->position.y, 0);
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_STRIP);
    switch (this->pivot) {
    case pivotPosition::CENTER:
        glVertex2f(-this->width / 2, -this->height / 2);
        glVertex2f(this->width / 2, -this->height / 2);
        glVertex2f(this->width / 2, this->height / 2);
        glVertex2f(-this->width / 2, this->height / 2);
        glVertex2f(-this->width / 2, -this->height / 2);
        glVertex2f(this->width / 2, this->height / 2);
        break;
    case pivotPosition::BOT_LEFT:
        glVertex2f(0, -this->height);
        glVertex2f(this->width, -this->height);
        glVertex2f(this->width, 0);
        glVertex2f(0, 0);
        glVertex2f(0, -this->height);
        glVertex2f(this->width, 0);
        break;
    case pivotPosition::TOP_LEFT:
        glVertex2f(0, 0);
        glVertex2f(0, this->height);
        glVertex2f(this->width, this->height);
        glVertex2f(this->width, 0);
        glVertex2f(0, 0);
        glVertex2f(this->width, this->height);
        break;
    }
    glEnd();
    glPopMatrix();
}

void Collider::idle() {
    if (this->owner != nullptr)
        this->position = this->owner->getPosition();
}