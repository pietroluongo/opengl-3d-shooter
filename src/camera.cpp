#include "../include/camera.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#define WINDOW_WIDTH_TMP 500
#define WINDOW_HEIGHT_TMP 500

Camera::Camera() {}
void Camera::idle() {
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glOrtho(-WINDOW_WIDTH_TMP + this->bounds.x,
            WINDOW_WIDTH_TMP + this->bounds.x,
            WINDOW_HEIGHT_TMP + this->bounds.y,
            -WINDOW_HEIGHT_TMP + this->bounds.y, -1, 1);
}
glm::ivec4 Camera::getBounds() {
    return glm::ivec4(-10 + this->bounds.x, 10 + this->bounds.x,
                      10 + this->bounds.y, -10 + this->bounds.y);
}
void Camera::moveBoundsX(int x) { this->bounds.x += x; }
void Camera::moveBoundsY(int y) { this->bounds.y += y; }