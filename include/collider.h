#ifndef COLLIDER_H
#define COLLIDER_H
#include "customTypes.h"
#include "object.h"

class Collider {
  private:
    glfvec2 position;
    float width, height;
    pivotPosition pivot;
    Object* owner = nullptr;

  public:
    Collider(float x, float y, float w, float h, Object* owner = nullptr,
             pivotPosition pivot = pivotPosition::TOP_LEFT);
    void draw();
    void idle();
    bool collidesWith(Collider* other);
    glm::fvec4 getBoundingBox();
    glm::fvec2 getCenter();
};

#endif