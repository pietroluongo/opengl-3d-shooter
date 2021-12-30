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
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glOrtho(center.x - CAMERA_WIDTH, center.x + CAMERA_WIDTH,
            center.y + CAMERA_HEIGHT, center.y - CAMERA_HEIGHT, -1, 1);
}
glm::ivec4 Camera::getBounds() {
    return glm::ivec4(center.x - CAMERA_WIDTH, center.x + CAMERA_WIDTH,
                      center.y + CAMERA_HEIGHT, center.y - CAMERA_HEIGHT);
}
void Camera::moveX(int x) { this->center.x += x; }
void Camera::moveY(int y) { this->center.y += y; }

void Camera::setCenter(glm::vec2 focus) {
    this->bounds.x = focus.x - BASE_CAMERA_WIDTH;
    this->bounds.y = focus.y - BASE_CAMERA_HEIGHT;
}

glm::ivec2 Camera::getPosition() { return glm::vec2(center.x, center.y); }