#ifndef COLLIDER_H
#define COLLIDER_H
#include "customTypes.h"
#include "object.h"

struct BoundingBox3D {
    glm::fvec3 min;
    glm::fvec3 max;
};

class Collider {
  private:
    glm::fvec3 position;
    float width, height, depth;
    pivotPosition pivot;
    Object* owner = nullptr;
    bool enabled = true;

  public:
    Collider(float x, float y, float z, float w, float h, float d,
             Object* owner = nullptr,
             pivotPosition pivot = pivotPosition::TOP_LEFT);
    ~Collider();
    void draw();
    void idle();
    BoundingBox3D getBoundingBox();
    glm::fvec3 getCenter();
    bool overlaps(Collider* other);
    glm::bvec4 getOverlapDirection(Collider* other, glm::bvec4 oldDirection);
    void resize(float w, float h, float d);
    void enable() { this->enabled = true; }
    void disable() { this->enabled = false; }
};

#endif