#ifndef PLATFORM_H
#define PLATFORM_H
#include "collider.h"
#include "customTypes.h"

class Platform {
  private:
    glfvec2 position;
    float width, height;
    glfvec3 color;
    pivotPosition pivot;
    Collider* collider;

    void drawAxis();

  public:
    Platform(float x, float y, float w, float h,
             pivotPosition pivot = pivotPosition::TOP_LEFT);
    ~Platform();
    void draw();
    Collider* getCollider();
};

#endif