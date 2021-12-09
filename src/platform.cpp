#include "../include/platform.h"

Platform::Platform(float x, float y, float w, float h) {
    this->position = glivec2(x, y);
    this->width = w;
    this->height = h;
}

void Platform::draw() {
    glPushMatrix();
    glTranslatef(this->position.x, this->position.y, 0);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    {
        glVertex2f(-this->width / 2, -this->height / 2);
        glVertex2f(this->width / 2, -this->height / 2);
        glVertex2f(this->width / 2, this->height / 2);
        glVertex2f(-this->width / 2, this->height / 2);
    }
    glEnd();
    glPopMatrix();
}