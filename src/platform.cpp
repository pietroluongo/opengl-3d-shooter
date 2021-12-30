#include "../include/platform.h"
#include "../include/constants.h"
#include "../include/globalCtx.h"

extern GlobalCtx* context;

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
    case pivotPosition::BOT_LEFT:
        glVertex2f(0, -this->height);
        glVertex2f(this->width, -this->height);
        glVertex2f(this->width, 0);
        glVertex2f(0, 0);
        break;
    case pivotPosition::TOP_LEFT:
        glVertex2f(0, 0);
        glVertex2f(0, this->height);
        glVertex2f(this->width, this->height);
        glVertex2f(this->width, 0);
    }
    glEnd();

    if (context->shouldObjectsDrawCoordinateSystem) {
        this->drawAxis();
    }

    glPopMatrix();
}

void Platform::drawAxis() {

    glColor3f(1.0f, 1.0f, 1.0f);
    glPointSize(DEBUG_CENTER_POINT_SIZE);
    glBegin(GL_POINTS);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(DEBUG_AXIS_SIZE, 0.0f, 0.0f);

    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, DEBUG_AXIS_SIZE, 0.0f);

    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, DEBUG_AXIS_SIZE);
    glEnd();
}