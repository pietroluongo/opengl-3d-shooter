#ifndef CAMERA_H
#define CAMERA_H
#include "../libs/glm/glm.hpp"
#include "object.h"

class Camera {
    glm::fvec4 bounds = {0, 0, 0, 0};
    glm::fvec2 center = {0, 0};

    Object* followTarget = nullptr;

    double zoomLevel = 1.0;
    void updateBounds();
    void handleInput();

  public:
    bool shouldFollowTarget = false;
    bool freeCamEnabled = false;

    Camera();
    void idle();
    glm::fvec4 getBounds();
    glm::fvec2 getPosition();
    void moveX(float x);
    void moveY(float y);
    void setCenter(glm::fvec2 focus);
    void setFollowTarget(Object* target);
};

#endif