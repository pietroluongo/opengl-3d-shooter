#ifndef PLATFORM_H
#define PLATFORM_H
#include "customTypes.h"

enum pivotPosition {
    TOP_LEFT,
    CENTER,
};

class Platform {
  private:
    glfvec2 position;
    float width, height;
    glfvec3 color;
    pivotPosition pivot;

    void drawAxis();

  public:
    Platform(float x, float y, float w, float h,
             pivotPosition pivot = pivotPosition::TOP_LEFT);
    void draw();
};

#endif