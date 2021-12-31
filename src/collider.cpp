#include "../include/collider.h"
#include <cmath>
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
    glm::fvec2 thisCenter = this->getCenter();
    glTranslatef(thisCenter.x, thisCenter.y, 0);
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_STRIP);
    {
        glVertex2f(-this->width / 2, this->height / 2);
        glVertex2f(this->width / 2, this->height / 2);
        glVertex2f(this->width / 2, -this->height / 2);
        glVertex2f(-this->width / 2, -this->height / 2);
        glVertex2f(-this->width / 2, this->height / 2);
        glVertex2f(this->width / 2, -this->height / 2);
    }
    glEnd();
    glPopMatrix();
}

void Collider::idle() {
    if (this->owner != nullptr)
        this->position = this->owner->getPosition();
}

bool Collider::collidesWith(Collider* other) {
    glm::fvec4 thisBoundingBox = this->getBoundingBox();
    glm::fvec4 otherBoundingBox = other->getBoundingBox();
    return this->collidesVerticallyWith(other) ||
           this->collidesHorizontallyWith(other);
}

bool Collider::collidesVerticallyWith(Collider* other) {
    glm::fvec4 thisBoundingBox = this->getBoundingBox();
    glm::fvec4 otherBoundingBox = other->getBoundingBox();
    if (thisBoundingBox[0] < otherBoundingBox[1] &&
        thisBoundingBox[1] > otherBoundingBox[0]) {
        if (abs(thisBoundingBox[3] - otherBoundingBox[2]) < 0.0001) {
            return true;
        }
    }
    return false;
}

bool Collider::collidesHorizontallyWith(Collider* other) {
    glm::fvec4 thisBoundingBox = this->getBoundingBox();
    glm::fvec4 otherBoundingBox = other->getBoundingBox();
    if (thisBoundingBox[2] < otherBoundingBox[3] &&
        thisBoundingBox[3] > otherBoundingBox[2]) {
        if (abs(thisBoundingBox[1] - otherBoundingBox[0]) < 0.0001) {
            return true;
            printf("Collided!\n");
        }
    }
    return false;
}

/**
 * @brief Gets the bounding box of the collider.
 *
 * @return glm::fvec4 [left, right, top, bottom]
 */
glm::fvec4 Collider::getBoundingBox() {
    switch (this->pivot) {
    case pivotPosition::CENTER:
        return glm::fvec4(this->position.x - this->width / 2,
                          this->position.x + this->width / 2,
                          this->position.y - this->height / 2,
                          this->position.y + this->height / 2);
    case pivotPosition::BOT_LEFT:
        return glm::fvec4(this->position.x, this->position.x + this->width,
                          this->position.y - this->height, this->position.y);
    case pivotPosition::TOP_LEFT:
    default:
        return glm::fvec4(this->position.x, this->position.x + this->width,
                          this->position.y, this->position.y + this->height);
    }
}

glm::fvec2 Collider::getCenter() {
    switch (this->pivot) {
    case pivotPosition::CENTER:
        return glm::fvec2(this->position.x, this->position.y);
    case pivotPosition::BOT_LEFT:
        return glm::fvec2(this->position.x + this->width / 2,
                          this->position.y - this->height / 2);
    case pivotPosition::TOP_LEFT:
    default:
        return glm::fvec2(this->position.x + this->width / 2,
                          this->position.y + this->height / 2);
    }
}