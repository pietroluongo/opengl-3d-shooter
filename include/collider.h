#ifndef COLLIDER_H
#define COLLIDER_H
#include "customTypes.h"
#include "object.h"

class Collider {
  private:
    glm::fvec2 position;
    float width, height;
    pivotPosition pivot;
    Object* owner = nullptr;

  public:
    Collider(float x, float y, float w, float h, Object* owner = nullptr,
             pivotPosition pivot = pivotPosition::TOP_LEFT);
    void draw();
    void idle();
    glm::fvec4 getBoundingBox();
    glm::fvec2 getCenter();
    bool overlaps(Collider* other);
    glm::bvec4 getOverlapDirection(Collider* other);
    void resize(float w, float h);
};

#endif