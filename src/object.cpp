#include "../include/object.h"
#include "../include/constants.h"
#include "../include/globalCtx.h"

extern GlobalCtx* context;

Object::Object(GLfloat x, GLfloat y) { this->position = {x, y}; }

Object::Object() {}

void Object::moveX(double amount) {
    this->position.x += (amount * context->getDeltaTime());
};

void Object::moveY(double amount) {
    this->position.y += (amount * context->getDeltaTime());
};

void Object::setPosition(glfvec2 position) { this->position = position; }

void Object::setPosition(float x, float y) { this->position = {x, y}; }

glfvec2 Object::getPosition() { return this->position; }

void Object::drawAxis() {

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

void Object::accelerateX(double amount) {
    this->speed.x += (amount * context->getDeltaTime());
    if (this->speed.x > this->maxSpeed.x) {
        this->speed.x = this->maxSpeed.x;
    } else if (this->speed.x < -this->maxSpeed.x) {
        this->speed.x = -this->maxSpeed.x;
    }
};

void Object::accelerateY(double amount) {
    this->speed.y += (amount * context->getDeltaTime());

    if (this->speed.y > this->maxSpeed.y) {
        this->speed.y = this->maxSpeed.y;
    } else if (this->speed.y < -this->maxSpeed.y) {
        this->speed.y = -this->maxSpeed.y;
    }
};

void Object::idle() {
    if (this->speed.x > 0) {
        this->speed.x -= this->speedFalloff.x * context->getDeltaTime();
    } else if (this->speed.x < 0) {
        this->speed.x += this->speedFalloff.x * context->getDeltaTime();
    }
    if (this->speed.y > 0) {
        this->speed.y -= this->speedFalloff.y * context->getDeltaTime();
    } else if (this->speed.y < 0) {
        this->speed.y += this->speedFalloff.y * context->getDeltaTime();
    }
}