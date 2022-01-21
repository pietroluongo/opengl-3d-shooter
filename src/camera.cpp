#include "../include/camera.h"
#include "../include/globalCtx.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define BASE_CAMERA_WIDTH 100
#define BASE_CAMERA_HEIGHT 100

constexpr float CAMERA_SPEED = 50.0f;

constexpr float CAMERA_WIDTH = BASE_CAMERA_WIDTH / 2;
constexpr float CAMERA_HEIGHT = BASE_CAMERA_HEIGHT / 2;

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
    this->bounds[0] = center.x - (CAMERA_WIDTH * this->zoomLevel);
    this->bounds[1] = center.x + (CAMERA_WIDTH * this->zoomLevel);
    this->bounds[2] = center.y + (CAMERA_HEIGHT * this->zoomLevel);
    this->bounds[3] = center.y - (CAMERA_HEIGHT * this->zoomLevel);
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