#include "../include/platform.h"

Platform::Platform(float x, float y, float w, float h, pivotPosition pivot) {
    this->position = glivec2(x, y);
    this->width = w;
    this->height = h;
    this->pivot = pivot;
}

void Platform::draw() {
    glPushMatrix();
    glTranslatef(this->position.x, this->position.y, 0);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    switch (this->pivot) {
    case pivotPosition::CENTER:
        glVertex2f(-this->width / 2, -this->height / 2);
        glVertex2f(this->width / 2, -this->height / 2);
        glVertex2f(this->width / 2, this->height / 2);
        glVertex2f(-this->width / 2, this->height / 2);
        break;
    case pivotPosition::TOP_LEFT:
        glVertex2f(0, -this->height);
        glVertex2f(this->width, -this->height);
        glVertex2f(this->width, 0);
        glVertex2f(0, 0);
        break;
    }
    glEnd();
    glPopMatrix();
}