#ifndef PLATFORM_H
#define PLATFORM_H
#include "collider.h"
#include "customTypes.h"
#include "solidUtils.h"

#define DEFAULT_TEX 1

enum PlatformType {
    PLATFORM_TOP,
    PLATFORM_LEFT,
    PLATFORM_RIGHT,
    PLATFORM_BOTTOM,
    PLATFORM_GENERIC,
    PLATFORM_INVISIBLE,
};

class Platform {
  private:
    glfvec2 position;
    glfvec3 color = {.7f, .7f, .7f};
    float width, height;
    pivotPosition pivot;
    std::unique_ptr<Collider> collider;
    float depth = 0;

    void drawAxis();

    CubeTextureData textureData =
        CubeTextureData(DEFAULT_TEX, DEFAULT_TEX, DEFAULT_TEX, DEFAULT_TEX,
                        DEFAULT_TEX, DEFAULT_TEX);
    PlatformType type = PLATFORM_GENERIC;

  public:
    Platform(float x, float y, float w, float h,
             PlatformType type = PLATFORM_GENERIC,
             pivotPosition pivot = pivotPosition::TOP_LEFT);
    ~Platform();
    void draw();
    Collider* getCollider();
    void setColor(glfvec3 color);
    void setDepth(float depth);

    void updateTextures();
};

#endif