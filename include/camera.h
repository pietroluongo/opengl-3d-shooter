#ifndef CAMERA_H
#define CAMERA_H
#include "../libs/glm/glm.hpp"
#include "object.h"

enum CameraFollowMode {
    CAMERA_FOLLOW_MODE_NONE,
    CAMERA_FOLLOW_MODE_SINGLE_AXIS,
    CAMERA_FOLLOW_MODE_DUAL_AXIS
};

enum CameraMode { CAMERA_2D, CAMERA_3D };

enum CameraBehaviour {
    CAMERA_FPS,
    CAMERA_TPS,
    CAMERA_AIM,
    CAMERA_FREE,
    CAMERA_ORBIT,
    CAMERA_2D_PERSPECTIVE
};

class Camera {
  private:
    glm::fvec4 bounds = {0, 0, 0, 0};
    glm::fvec3 center = {0, 0, 0};
    glm::fvec3 position = {0, 0, 0};

    glm::fvec3 up = {0, -1, 0};
    glm::fvec3 forward = {0, 0, 1};

    glm::fvec2 size = {0, 0};

    // For CAMERA_FOLLOW_SINGLE_AXIS
    float targetYCoordinate = 0;

    Object* followTarget = nullptr;

    void updateBounds();
    void handleInput();

    CameraFollowMode followMode = CAMERA_FOLLOW_MODE_NONE;
    CameraMode mode = CAMERA_2D;
    CameraBehaviour behaviour = CAMERA_2D_PERSPECTIVE;

    glm::mat4 projectionMatrix = glm::mat4(1.0f);

  public:
    bool shouldFollowTarget = false;
    bool freeCamEnabled = false;
    float zoomLevel = .5f;
    float xzAngle = 0;
    float xyAngle = 0;

    glm::fvec2 lastMousePosition = {0, 0};

    Camera();
    Camera(CameraMode mode);
    void idle();
    glm::fvec4 getBounds();
    glm::fvec3 getCenter();
    glm::fvec3 getPosition();
    void moveForward(float amount);
    void moveX(float x);
    void moveY(float y);
    void moveZ(float z);
    void rotateX(float x);
    void rotateY(float y);
    void rotateZ(float z);
    void setCenter(glm::fvec3 focus);
    void setPosition(glm::fvec3 pos);
    void setFollowTarget(Object* target);
    void setFollowMode(CameraFollowMode mode);
    void setTargetYCoordinates(float y);
    void moveSidesFromForward(float amount);
    void setDesiredSize(glm::fvec2 size);
    glm::fvec2 getSize() { return this->size; };
    glm::mat4 getProjectionMatrix() { return this->projectionMatrix; };
    const char* getCameraMode() {
        if (this->mode == CAMERA_2D) {
            return "2D";
        } else {
            return "3D";
        }
    };
    const char* getCameraBehaviour();
    void setCameraBehaviour(CameraBehaviour behaviour);
};

#endif