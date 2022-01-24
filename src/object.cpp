#include "../include/object.h"
#include "../include/constants.h"
#include "../include/globalCtx.h"

extern GlobalCtx* context;

Object::Object(GLfloat x, GLfloat y, GLfloat size) {
    this->position = {x, y};
    this->size = size;
    this->collider =
        new Collider(x, y, size, size, this, pivotPosition::CENTER);
    this->reacquireColliders();
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
    this->currentTime += context->getDeltaTime();
    this->collisionDirections = {false, false, false, false};
    this->isGrounded = false;
    this->collider->idle();

    for (auto otherCollider : this->colliders) {
        if (this->collider->overlaps(otherCollider)) {
            this->collisionDirections = this->collider->getOverlapDirection(
                otherCollider, collisionDirections);
            if (this->collisionDirections[0] && this->positionDelta.x < 0) {
                this->positionDelta.x = 0;
            }
            if (this->collisionDirections[1] && this->positionDelta.x > 0) {
                this->positionDelta.x = 0;
            }
            if (this->collisionDirections[3] && this->positionDelta.y > 0) {
                this->positionDelta.y = 0;
            }
            if (this->collisionDirections[2] && this->positionDelta.y < 0) {
                this->positionDelta.y = 0;
            }

            if (this->collisionDirections[3]) {
                this->isGrounded = true;
            }
        }
    }

    if (this->isGrounded) {
        this->fallTimer = 0;
    }

    if (!this->isGrounded && this->isAffectedByGravity) {
        // if (currentTime - lastGroundedTime < 2) {
        //     this->moveY(15 * (this->currentTime - this->lastGroundedTime));
        // } else {
        //     this->moveY(15 *
        //                 ((this->currentTime - this->lastGroundedTime) - 2));
        // }
        this->moveY(15 * fallTimer);
        this->fallTimer += context->getDeltaTime();
    }

    this->position += this->positionDelta;
    this->positionDelta = {0, 0};
}

Collider* Object::getCollider() { return this->collider; }

void Object::teleport(float x, float y) {
    this->position = {x, y};
    this->collider->idle();
}

void Object::teleportToGround() {
    while (1) {
        glfvec2 oldPosition = this->position;
        this->position.y += 1;
        this->collider->idle();
        for (auto otherCollider : this->colliders) {
            if (this->collider->overlaps(otherCollider)) {
                this->position = oldPosition;
                this->position.y += .01;
                this->collider->idle();
                return;
            }
        }
    }
}

void Object::setIsAffectedByGravity(bool isAffected) {
    this->isAffectedByGravity = isAffected;
}

void Object::reacquireColliders() {
    this->colliders = context->getGameRef()->getAllObjectColliders();
}