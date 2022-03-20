#ifndef SOLID_UTILS_H
#define SOLID_UTILS_H
#include "../libs/glm/glm.hpp"
#include <memory>

enum PivotPoint {
    PIVOT_CENTER,
    PIVOT_LEFT_TOP,
    PIVOT_CENTER_BOTTOM,
};

struct VertexData {
    glm::fvec3 pos;
    glm::fvec3 nrm;
    glm::fvec2 txC;
};

struct CubeTextureData {
    unsigned int top;
    unsigned int bottom;
    unsigned int left;
    unsigned int right;
    unsigned int front;
    unsigned int back;
};

enum TexTileMode {
    TEX_TILE_MODE_TILE,
    TEX_TILE_MODE_STRETCH,
};

void drawCubeFromExtrude(float depth, glm::vec3 color, glm::vec3 points[4],
                         CubeTextureData textures,
                         TexTileMode tileMode = TEX_TILE_MODE_TILE);

void drawCoordinateSystem();

class Sphere {
  private:
    std::unique_ptr<VertexData> vertices;
    int vertexCount;
    double radius;
    unsigned int tex = -1;

  public:
    Sphere(double radius, double space);
    ~Sphere();
    void setTexture(unsigned int tex) { this->tex = tex; }
    void draw();
};

#endif