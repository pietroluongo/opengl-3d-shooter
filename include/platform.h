#ifndef PLATFORM_H
#define PLATFORM_H
#include "customTypes.h"

class Platform {
  private:
    glfvec2 position;
    float width, height;
    glfvec3 color;

  public:
    Platform(float x, float y, float w, float h);
    void draw();
};

#endif