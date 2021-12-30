#ifndef CAMERA_H
#define CAMERA_H
#include "../libs/glm/glm.hpp"
#include "object.h"

class Camera {
    glm::fvec4 bounds = {0, 0, 0, 0};
    glm::fvec2 center = {0, 0};

    Object* followTarget = nullptr;

    bool shouldFollowTarget = false;
    double zoomLevel = 1.0;
    void updateBounds();

  public:
    Camera();
    void idle();
    glm::fvec4 getBounds();
    glm::fvec2 getPosition();
    void moveX(int x);
    void moveY(int y);
    void setCenter(glm::vec2 focus);
    void setFollowTarget(Object* target);
};

#endif