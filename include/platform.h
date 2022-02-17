#ifndef PLATFORM_H
#define PLATFORM_H
#include "collider.h"
#include "customTypes.h"

class Platform {
  private:
    glfvec2 position;
    glfvec3 color = {1.0f, 1.0f, 1.0f};
    float width, height;
    pivotPosition pivot;
    std::unique_ptr<Collider> collider;

    void drawAxis();

  public:
    Platform(float x, float y, float w, float h,
             pivotPosition pivot = pivotPosition::TOP_LEFT);
    ~Platform();
    void draw();
    Collider* getCollider();
    void setColor(glfvec3 color);
};

#endif