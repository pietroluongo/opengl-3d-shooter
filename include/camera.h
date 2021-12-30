#ifndef CAMERA_H
#define CAMERA_H
#include "../libs/glm/glm.hpp"

class Camera {
    glm::ivec4 bounds = {0, 0, 0, 0};
    glm::ivec2 center = {0, 0};

    double zoomLevel = 1.0;
    void updateBounds();

  public:
    Camera();
    void idle();
    glm::ivec4 getBounds();
    glm::ivec2 getPosition();
    void moveX(int x);
    void moveY(int y);
    void setCenter(glm::vec2 focus);
};

#endif