#include "../include/object.h"
#include "../include/constants.h"
#include "../include/globalCtx.h"
#include "../libs/glm/gtx/rotate_vector.hpp"

#if defined(_WIN32) || defined(WIN32)
#define M_PI 3.14159265358979323846
#endif

extern GlobalCtx* context;

Object::Object(GLfloat x, GLfloat y, GLfloat z, GLfloat size) {
    this->position = {x, y, z};
    this->size = size;
    this->collider = std::unique_ptr<Collider>(
        new Collider(x, y, z, size, size, size, this, pivotPosition::CENTER));
}

Object::Object() {}
Object::~Object() {}

void Object::moveForward(float distance) {
    // const glm::fvec3 forward = glm::normalize(this->rotation);
    const glm::fvec3 delta = distance * this->rotation;
    this->positionDelta += delta * (float)context->getDeltaTime();
}

void Object::moveX(double amount) {
    this->positionDelta.x += (amount * context->getDeltaTime());
};

void Object::moveY(double amount) {
    this->positionDelta.y += (amount * context->getDeltaTime());
};

void Object::moveZ(double amount) {
    this->positionDelta.z += (amount * context->getDeltaTime());
}

void Object::rotateX(double angle) {
    float actualAngle = angle * context->getDeltaTime();
    this->rotation = glm::rotateX(this->rotation, actualAngle);
    this->visualRotation.x += actualAngle * 180 / M_PI;
}

void Object::rotateY(double angle) {
    float actualAngle = angle * context->getDeltaTime();
    this->rotation = glm::rotateY(this->rotation, actualAngle);
    this->visualRotation.y += actualAngle * 180 / M_PI;
}

void Object::rotateZ(double angle) {

    float actualAngle = angle * context->getDeltaTime();
    this->rotation = glm::rotateZ(this->rotation, actualAngle);
    this->visualRotation.z += actualAngle * 180 / M_PI;
}

void Object::setPosition(glfvec2 position) {
    this->position = {position.x, position.y, 0};
}

void Object::setPosition(glfvec3 position) { this->position = position; }

void Object::setPosition(float x, float y, float z) {
    this->position = {x, y, z};
}

glfvec3 Object::getPosition() { return this->position; }

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

    for (auto colliderList : this->colliders()) {
        for (auto otherCollider : *colliderList) {
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
    }

    if (this->isGrounded) {
        this->fallTimer = 0;
    }

    if (!this->isGrounded && this->isAffectedByGravity) {
        this->moveY(this->size * 3.75 * fallTimer);
        this->fallTimer += context->getDeltaTime();
    }

    this->position += this->positionDelta;
    this->positionDelta = {0, 0, 0};
}

Collider* Object::getCollider() { return this->collider.get(); }

void Object::teleport(float x, float y, float z) {
    this->position = {x, y, z};
    this->collider->idle();
}

void Object::teleportToGround() {
    while (1) {
        if (this->position.y <
            context->getGameRef()->getMap()->getWorldBounds()[3]) {
            printf("[ERROR] Could not teleport object to ground.\n");
            return;
        }
        glfvec3 oldPosition = this->position;
        this->position.y += 1;
        this->collider->idle();
        for (auto colliderList : this->colliders()) {
            for (auto otherCollider : *colliderList) {
                if (this->collider->overlaps(otherCollider)) {
                    this->position = oldPosition;
                    this->position.y += .01;
                    this->collider->idle();
                    return;
                }
            }
        }
    }
}

void Object::setIsAffectedByGravity(bool isAffected) {
    this->isAffectedByGravity = isAffected;
}