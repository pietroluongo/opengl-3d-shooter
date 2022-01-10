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
    bool collidesWith(Collider* other);
    bool collidesVerticallyWith(Collider* other);
    bool collidesHorizontallyWith(Collider* other);
    glm::fvec4 getBoundingBox();
    glm::fvec2 getCenter();
    bool overlaps(Collider* other);
    bool collidesLeft(Collider* other);
    bool collidesRight(Collider* other);
};

#endif