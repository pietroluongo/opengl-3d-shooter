#include "../include/object.h"
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
