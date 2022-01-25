#include "../include/camera.h"
#include "../include/globalCtx.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define BASE_CAMERA_WIDTH 100
#define BASE_CAMERA_HEIGHT 100

constexpr float CAMERA_SPEED = 50.0f;

constexpr float DEFAULT_CAMERA_WIDTH = BASE_CAMERA_WIDTH / 2;
constexpr float DEFAULT_CAMERA_HEIGHT = BASE_CAMERA_HEIGHT / 2;

extern GlobalCtx* context;

Camera::Camera() {}

void Camera::idle() {
    this->handleInput();
    if (this->shouldFollowTarget) {
        this->setCenter(this->followTarget->getPosition());
    }
    this->shouldFollowTarget = !this->freeCamEnabled;
    this->updateBounds();
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glOrtho(this->bounds[0], this->bounds[1], this->bounds[2], this->bounds[3],
            -1, 1);
}

glm::fvec4 Camera::getBounds() { return this->bounds; }

void Camera::moveX(float x) { this->center.x += x * context->getDeltaTime(); }
void Camera::moveY(float y) { this->center.y += y * context->getDeltaTime(); }

void Camera::setCenter(glm::fvec2 focus) {
    this->center = focus;
    this->updateBounds();
}

void Camera::updateBounds() {
    float camHeight, camWidth;
    if (this->followMode == CAMERA_FOLLOW_MODE_SINGLE_AXIS) {
        camHeight = this->size.y;
        this->center.y = this->targetYCoordinate;
    } else if (this->followMode == CAMERA_FOLLOW_MODE_DUAL_AXIS) {
        camHeight = DEFAULT_CAMERA_HEIGHT;
    } else {
        camHeight = DEFAULT_CAMERA_HEIGHT;
    }
    if (this->followMode == CAMERA_FOLLOW_MODE_SINGLE_AXIS) {
        camWidth = camHeight;
    } else if (this->followMode == CAMERA_FOLLOW_MODE_DUAL_AXIS) {
        camWidth = DEFAULT_CAMERA_WIDTH;
    } else {
        camWidth = DEFAULT_CAMERA_WIDTH;
    }
    this->bounds[0] = center.x - (camWidth * this->zoomLevel);
    this->bounds[1] = center.x + (camWidth * this->zoomLevel);

    this->bounds[2] = center.y + (camHeight * this->zoomLevel);
    this->bounds[3] = center.y - (camHeight * this->zoomLevel);
}

glm::fvec2 Camera::getPosition() { return glm::fvec2(center.x, center.y); }

void Camera::setFollowTarget(Object* target) {
    this->followTarget = target;
    this->shouldFollowTarget = true;
}

void Camera::handleInput() {
    if (this->freeCamEnabled) {
        if (context->isKeyPressed('l')) {
            this->moveX(CAMERA_SPEED);
        }
        if (context->isKeyPressed('j')) {
            this->moveX(-CAMERA_SPEED);
        }
        if (context->isKeyPressed('i')) {
            this->moveY(-CAMERA_SPEED);
        }
        if (context->isKeyPressed('k')) {
            this->moveY(CAMERA_SPEED);
        }
    }
}

void Camera::setFollowMode(CameraFollowMode mode) { this->followMode = mode; }

void Camera::setTargetYCoordinates(float y) { this->targetYCoordinate = y; }

void Camera::setDesiredSize(glm::fvec2 size) { this->size = size; }