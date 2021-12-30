#include "../include/camera.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define BASE_CAMERA_WIDTH 100
#define BASE_CAMERA_HEIGHT 100

constexpr int CAMERA_WIDTH = BASE_CAMERA_WIDTH / 2;
constexpr int CAMERA_HEIGHT = BASE_CAMERA_HEIGHT / 2;

Camera::Camera() {}

void Camera::idle() {
    if (this->shouldFollowTarget) {
        this->setCenter(this->followTarget->getPosition());
    }
    this->updateBounds();
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glOrtho(this->bounds[0], this->bounds[1], this->bounds[2], this->bounds[3],
            -1, 1);
}

glm::fvec4 Camera::getBounds() { return this->bounds; }

void Camera::moveX(int x) { this->center.x += x; }
void Camera::moveY(int y) { this->center.y += y; }

void Camera::setCenter(glm::vec2 focus) {
    this->center = focus;
    this->updateBounds();
}

void Camera::updateBounds() {
    this->bounds[0] = center.x - CAMERA_WIDTH;
    this->bounds[1] = center.x + CAMERA_WIDTH;
    this->bounds[2] = center.y + CAMERA_HEIGHT;
    this->bounds[3] = center.y - CAMERA_HEIGHT;
}

glm::fvec2 Camera::getPosition() { return glm::vec2(center.x, center.y); }

void Camera::setFollowTarget(Object* target) {
    this->followTarget = target;
    this->shouldFollowTarget = true;
}