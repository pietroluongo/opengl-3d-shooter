#include "../include/collider.h"
#include <cstdio>
#include <cstdlib>

Collider::Collider(float x, float y, float z, float w, float h, float d,
                   Object* owner, pivotPosition pivot) {
    this->position = glfvec3(x, y, z);
    this->width = w;
    this->height = h;
    this->depth = d;
    this->pivot = pivot;
    this->owner = owner;
}

Collider::~Collider(){};

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

bool Collider::overlaps(Collider* other) {
    if (this->owner == other->owner || !this->enabled || !other->enabled)
        return false;
    BoundingBox3D thisBoundingBox = this->getBoundingBox();
    BoundingBox3D otherBoundingBox = other->getBoundingBox();

    // glm::fvec4 selfBox = {thisBoundingBox.min.x, thisBoundingBox.max.x,
    //                       thisBoundingBox.min.y, thisBoundingBox.max.y};

    // glm::fvec4 otherBox = {otherBoundingBox.min.x, otherBoundingBox.max.x,
    //                        otherBoundingBox.min.y, otherBoundingBox.max.y};

    // if (selfBox[0] <= otherBox[1] && selfBox[1] >= otherBox[0] &&
    //     selfBox[2] <= otherBox[3] && selfBox[3] >= otherBox[2]) {
    //     return true;
    // }

    if (thisBoundingBox.min.x <= otherBoundingBox.max.x &&
        thisBoundingBox.max.x >= otherBoundingBox.min.x &&
        thisBoundingBox.min.y <= otherBoundingBox.max.y &&
        thisBoundingBox.max.y >= otherBoundingBox.min.y &&
        thisBoundingBox.min.z <= otherBoundingBox.max.z &&
        thisBoundingBox.max.z >= otherBoundingBox.min.z) {
        return true;
    }
    return false;
}

/**
 * @brief Gets the bounding box of the collider.
 *
 * @return glm::fvec4 [left, right, top, bottom]
 */
BoundingBox3D Collider::getBoundingBox() {
    switch (this->pivot) {
    case pivotPosition::CENTER:
        return {glm::fvec3(this->position.x - this->width / 2,
                           this->position.y - this->height / 2,
                           this->position.z - this->depth / 2),
                glm::fvec3(this->position.x + this->width / 2,
                           this->position.y + this->height / 2,
                           this->position.z + this->depth / 2)};
    case pivotPosition::BOT_LEFT:
        return {
            glm::fvec3(this->position.x, this->position.y, this->position.z),
            glm::fvec3(this->position.x + this->width,
                       this->position.y + this->height,
                       this->position.z + this->depth)};
    case pivotPosition::TOP_LEFT:
    default:
        return {
            glm::fvec3(this->position.x, this->position.y, this->position.z),
            glm::fvec3(this->position.x + this->width,
                       this->position.y + this->height,
                       this->position.z + this->depth)};
    }
}

glm::fvec3 Collider::getCenter() {
    switch (this->pivot) {
    case pivotPosition::CENTER:
        return glm::fvec3(this->position.x, this->position.y, this->position.z);
    case pivotPosition::BOT_LEFT:
        return glm::fvec3(this->position.x + this->width / 2,
                          this->position.y - this->height / 2,
                          this->position.z - this->depth / 2);
    case pivotPosition::TOP_LEFT:
    default:
        return glm::fvec3(this->position.x + this->width / 2,
                          this->position.y + this->height / 2,
                          this->position.z + this->depth / 2);
    }
}

glm::bvec4 Collider::getOverlapDirection(Collider* other,
                                         glm::bvec4 oldDirection) {
    glm::fvec2 thisCenter = this->getCenter();
    glm::fvec2 otherCenter = other->getCenter();
    glm::bvec4 overlapDirection = oldDirection;

    float dx = otherCenter.x - thisCenter.x;
    float px = (other->width / 2 + this->width / 2) - std::abs(dx);

    float dy = otherCenter.y - thisCenter.y;
    float py = (other->height / 2 + this->height / 2) - std::abs(dy);

    if (px < py) {
        int sx = dx < 0 ? -1 : 1;
        if (sx >= 0) {
            overlapDirection[1] = true;
        } else {
            overlapDirection[0] = true;
        }
    } else {
        int sy = dy < 0 ? -1 : 1;
        if (sy >= 0) {
            overlapDirection[3] = true;
        } else {
            overlapDirection[2] = true;
        }
    }

    return overlapDirection;
}

void Collider::resize(float width, float height, float depth) {
    this->width = width;
    this->height = height;
    this->depth = depth;
}