#ifndef COLLIDER_H
#define COLLIDER_H
#include "customTypes.h"

class Collider {
  private:
    glfvec2 position;
    float width, height;
    pivotPosition pivot;

  public:
    Collider(float x, float y, float w, float h,
             pivotPosition pivot = pivotPosition::TOP_LEFT);
    void draw();
};

#endif