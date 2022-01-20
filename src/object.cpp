#include "../include/object.h"
#include "../include/constants.h"
#include "../include/globalCtx.h"

extern GlobalCtx* context;

Object::Object(GLfloat x, GLfloat y, GLfloat size) {
    this->position = {x, y};
    this->size = size;
    this->collider =
        new Collider(x, y, size, size, this, pivotPosition::CENTER);
    this->colliders = context->getGameRef()->getAllObjectColliders();
}

Object::Object() {}
Object::~Object() {}

void Object::moveX(double amount) {
    this->positionDelta.x += (amount * context->getDeltaTime());
};

void Object::moveY(double amount) {
    this->positionDelta.y += (amount * context->getDeltaTime());
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

void Object::idle() {
    this->collisionDirections = {false, false, false, false};
    this->isGrounded = false;
    bool hasCollided = false;
    this->collider->idle();
    for (auto otherCollider : this->colliders) {
        if (this->collider->overlaps(otherCollider)) {
            hasCollided = true;
            break;
        }
    }

    if (!this->isGrounded) {
        this->moveY(1);
    }

    if (!hasCollided) {
        this->position += this->positionDelta;
    }

    this->positionDelta = {0, 0};
}

Collider* Object::getCollider() { return this->collider; }
