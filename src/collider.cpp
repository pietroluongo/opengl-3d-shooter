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

bool Collider::collidesWith(Collider* other) {
    glm::fvec2 thisCenter = this->getCenter();
    glm::fvec2 otherCenter = other->getCenter();
    printf("Comparing %f, %f and %f, %f\n", thisCenter.x, thisCenter.y,
           otherCenter.x, otherCenter.y);
    float dist = abs((this->position.x + this->width / 2) -
                     (other->position.x + other->width / 2));
    if (dist < 0.001f)
        return true;
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