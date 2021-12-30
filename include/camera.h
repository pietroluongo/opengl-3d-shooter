#ifndef CAMERA_H
#define CAMERA_H
#include "../libs/glm/glm.hpp"
#include "object.h"

class Camera {
    glm::fvec4 bounds = {0, 0, 0, 0};
    glm::fvec2 center = {0, 0};

    Object* followTarget = nullptr;

    void updateBounds();
    void handleInput();

  public:
    bool shouldFollowTarget = false;
    bool freeCamEnabled = false;
    float zoomLevel = 2.0f;

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