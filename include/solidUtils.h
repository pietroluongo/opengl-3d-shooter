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

void drawCube(glm::vec3 pos = glm::vec3(0, 0, 0),
              glm::vec3 size = glm::vec3(1, 1, 1),
              glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f));

void drawCubePure(glm::vec3 size = glm::vec3(1, 1, 1),
                  glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f),
                  PivotPoint pivot = PIVOT_CENTER);

void drawCubeFromExtrude(float depth, glm::vec3 color, glm::vec3 points[4]);

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