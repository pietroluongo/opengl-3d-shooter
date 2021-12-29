#ifndef CAMERA_H
#define CAMERA_H
#include "../libs/glm/glm.hpp"

class Camera {
    glm::ivec2 bounds = {0, 0};

  public:
    Camera();
    void idle();
    glm::ivec4 getBounds();
    void moveBoundsX(int x);
    void moveBoundsY(int y);
};

#endif