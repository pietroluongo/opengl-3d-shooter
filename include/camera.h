#ifndef CAMERA_H
#define CAMERA_H
#include "../libs/glm/glm.hpp"
#include "object.h"

enum CameraFollowMode {
    CAMERA_FOLLOW_MODE_NONE,
    CAMERA_FOLLOW_MODE_SINGLE_AXIS,
    CAMERA_FOLLOW_MODE_DUAL_AXIS
};

class Camera {
    glm::fvec4 bounds = {0, 0, 0, 0};
    glm::fvec2 center = {0, 0};

    glm::fvec2 size = {0, 0};

    // For CAMERA_FOLLOW_SINGLE_AXIS
    float targetYCoordinate = 0;

    Object* followTarget = nullptr;

    void updateBounds();
    void handleInput();

    CameraFollowMode followMode = CAMERA_FOLLOW_MODE_NONE;

  public:
    bool shouldFollowTarget = false;
    bool freeCamEnabled = false;
    float zoomLevel = .5f;

    Camera();
    void idle();
    glm::fvec4 getBounds();
    glm::fvec2 getPosition();
    void moveX(float x);
    void moveY(float y);
    void setCenter(glm::fvec2 focus);
    void setFollowTarget(Object* target);
    void setFollowMode(CameraFollowMode mode);
    void setTargetYCoordinates(float y);
    void setDesiredSize(glm::fvec2 size);
    glm::fvec2 getSize() { return this->size; };
};

#endif