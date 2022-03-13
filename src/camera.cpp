#include "../include/camera.h"
#include "../include/globalCtx.h"
#include "../include/keymap.h"
#include "../libs/glm/ext/matrix_clip_space.hpp"
#include "../libs/glm/gtc/type_ptr.hpp"
#include "../libs/glm/gtx/rotate_vector.hpp"

#if defined(_WIN32) || defined(WIN32)
#include <windows.h>
#define M_PI 3.14159265358979323846
#endif

#include <GL/gl.h>
#include <GL/glu.h>

#ifdef USE_GLUT
#include <GL/glut.h>
#endif

#define BASE_CAMERA_WIDTH 100
#define BASE_CAMERA_HEIGHT 100

constexpr float CAMERA_SPEED = 50.0f;
constexpr float CAMERA_ROTATE_SPEED = 5.0f;

constexpr float DEFAULT_CAMERA_WIDTH = BASE_CAMERA_WIDTH / 2;
constexpr float DEFAULT_CAMERA_HEIGHT = BASE_CAMERA_HEIGHT / 2;

extern GlobalCtx* context;

Camera::Camera() {}
Camera::Camera(CameraMode mode) { this->mode = mode; }

void Camera::idle() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    this->handleInput();
    this->projectionMatrix = glm::mat4(1.0f);

    glm::ivec2 windowSize = context->getWindowSize();

    if (this->mode == CAMERA_2D) {
        if (this->shouldFollowTarget) {
            this->setCenter(this->followTarget->getPosition());
        }
        this->shouldFollowTarget = !this->freeCamEnabled;
        this->updateBounds();
        glOrtho(this->bounds[0], this->bounds[1], this->bounds[2],
                this->bounds[3], -1, 1);
    } else {
        this->projectionMatrix = glm::perspective(
            45.0f, (float)windowSize.x / (float)windowSize.y, 0.1f, 1000.0f);
        if (freeCamEnabled) {
            this->projectionMatrix *= glm::lookAt(
                this->position, this->position + this->forward, this->up);
        } else if (this->behaviour == CAMERA_FPS) {
            glm::ivec2 windowSize = context->getWindowSize();
            glm::fvec3 playerPosition =
                context->getGameRef()->getPlayer()->getPosition();
            this->projectionMatrix *=
                glm::lookAt(this->position, playerPosition, this->up);
        } else if (this->behaviour == CAMERA_TPS) {
            glm::fvec3 playerPosition =
                context->getGameRef()->getPlayer()->getPosition();
            glm::fvec3 playerDollyPosition =
                context->getGameRef()->getPlayer()->getDollyPosition();
            this->position = playerDollyPosition;
            this->projectionMatrix *=
                glm::lookAt(this->position, playerPosition, this->up);

        } else if (this->behaviour == CAMERA_ORBIT) {

            float cameraZoom = this->zoomLevel * 100.0f;
            glm::fvec3 playerPosition =
                context->getGameRef()->getPlayer()->getPosition();
            glm::fvec3 spherePosition = {0, 0, 0};
            spherePosition.x = cameraZoom * sin(xzAngle * M_PI / 180) *
                               cos((xyAngle * M_PI / 180));
            spherePosition.y = cameraZoom * sin((-xyAngle * M_PI / 180));
            spherePosition.z = cameraZoom * cos(xzAngle * M_PI / 180) *
                               cos((xyAngle * M_PI / 180));
            spherePosition += this->position;
            this->position = playerPosition;
            this->projectionMatrix *= glm::lookAt(
                spherePosition, playerPosition, glm::fvec3(0, -1, 0));
        }
        glMultMatrixf(glm::value_ptr(this->projectionMatrix));
        glMatrixMode(GL_MODELVIEW);
    }
}

glm::fvec4 Camera::getBounds() { return this->bounds; }

void Camera::moveX(float x) {
    this->center.x += x * context->getDeltaTime();
    this->position.x += x * context->getDeltaTime();
}
void Camera::moveY(float y) {
    this->center.y += y * context->getDeltaTime();
    this->position.y += y * context->getDeltaTime();
}

void Camera::moveForward(float amount) {
    this->position += amount * this->forward * (float)context->getDeltaTime();
}

void Camera::moveSidesFromForward(float amount) {
    this->position +=
        amount * glm::rotate(this->forward, glm::radians(90.0f), this->up) *
        (float)context->getDeltaTime();
}

void Camera::moveZ(float z) { this->position.z += z * context->getDeltaTime(); }

void Camera::rotateX(float x) {
    float angle = x * context->getDeltaTime();
    if (this->position.z > 0) {
        angle *= -1;
    }
    this->forward = glm::rotateX(this->forward, angle);
}

void Camera::rotateY(float y) {
    float angle = y * context->getDeltaTime();
    this->forward = glm::rotateY(this->forward, angle);
}

void Camera::rotateZ(float z) {
    float angle = z * context->getDeltaTime();
    this->forward = glm::rotateZ(this->forward, angle);
}

void Camera::setCenter(glm::fvec3 focus) {
    this->center = focus;
    this->updateBounds();
}

void Camera::setPosition(glm::fvec3 pos) { this->position = pos; }

void Camera::updateBounds() {
    float camHeight, camWidth;
    camHeight = this->size.y;
    this->center.y = this->targetYCoordinate;
    if (context->getWindowSize().x >= context->getWindowSize().y) {
        camWidth =
            camHeight * context->getWindowSize().x / context->getWindowSize().y;
    } else {
        camWidth =
            camHeight * context->getWindowSize().y / context->getWindowSize().x;
    }

    this->bounds[0] = center.x - (camWidth * this->zoomLevel);
    this->bounds[1] = center.x + (camWidth * this->zoomLevel);

    this->bounds[2] = center.y + (camHeight * this->zoomLevel);
    this->bounds[3] = center.y - (camHeight * this->zoomLevel);
}

glm::fvec3 Camera::getPosition() {
    return glm::fvec3(position.x, position.y, position.z);
}

glm::fvec3 Camera::getCenter() { return this->center; }

void Camera::setFollowTarget(Object* target) {
    this->followTarget = target;
    this->shouldFollowTarget = true;
}

void Camera::handleInput() {
    glm::fvec2 mousePos = context->getNormalizedMousePos();
    mousePos.x *= 100;
    mousePos.y *= 100;
    this->xzAngle += mousePos.x - this->lastMousePosition.x;
    this->xyAngle += mousePos.y - this->lastMousePosition.y;
    this->lastMousePosition = mousePos;
//     if (context->isKeyPressed(keymap::CAMERA_SET_THIRD_PERSON)) {
//         this->behaviour = CameraBehaviour::CAMERA_TPS;
//     }
//     if (context->isKeyPressed(keymap::CAMERA_TOGGLE_ORBIT)) {
//         this->behaviour = CAMERA_ORBIT;
// #ifdef USE_GLFW
//         glfwSetInputMode(context->getWindow(), GLFW_CURSOR,
//                          GLFW_CURSOR_DISABLED);
// #endif
//     } else {
// #ifdef USE_GLFW
//         glfwSetInputMode(context->getWindow(), GLFW_CURSOR,
//         GLFW_CURSOR_NORMAL);
// #endif
//     }
#ifdef USE_GLFW
    if (this->behaviour == CAMERA_ORBIT) {
        glfwSetInputMode(context->getWindow(), GLFW_CURSOR,
                         GLFW_CURSOR_DISABLED);
    } else {
        glfwSetInputMode(context->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
#endif
    // if (this->freeCamEnabled) {
    if (true) {
        // this->behaviour = CAMERA_FREE;
        if (this->mode == CAMERA_2D) {
            if (context->isKeyPressed(keymap::MOVE_CAMERA_RIGHT_BUTTON)) {
                this->moveX(CAMERA_SPEED);
            }
            if (context->isKeyPressed(keymap::MOVE_CAMERA_LEFT_BUTTON)) {
                this->moveX(-CAMERA_SPEED);
            }
            if (context->isKeyPressed(keymap::MOVE_CAMERA_UP_BUTTON)) {
                this->moveY(-CAMERA_SPEED);
            }
            if (context->isKeyPressed(keymap::MOVE_CAMERA_DOWN_BUTTON)) {
                this->moveY(CAMERA_SPEED);
            }
        } else {
            if (context->nAxes >= 4) {
                // X rotation: 5
                // Y rotation: 2
                // X movement: 0
                // Y movement: 1
                float rotX = 0, rotY = 0, rotZ = 0;
                float movX = 0, movY = 0, movZ = 0;
                if (abs(context->axes[2]) < 0.1)
                    rotY = 0;
                else
                    rotY = context->axes[2];

                if (abs(context->axes[5]) < 0.1)
                    rotX = 0;
                else
                    rotX = context->axes[5];

                if (abs(context->axes[0]) < 0.1)
                    movX = 0;
                else
                    movX = context->axes[0];

                if (abs(context->axes[1]) < 0.1)
                    movY = 0;
                else
                    movY = context->axes[1];
                this->rotateY(rotY * CAMERA_ROTATE_SPEED);
                this->rotateX(-rotX * CAMERA_ROTATE_SPEED);
                this->moveSidesFromForward(-movX * CAMERA_SPEED);
                this->moveForward(-movY * CAMERA_SPEED);
            }

            if (context->isKeyPressed(keymap::ROTATE_CAMERA_UP_BUTTON)) {
                this->rotateX(CAMERA_ROTATE_SPEED);
            }
            if (context->isKeyPressed(keymap::ROTATE_CAMERA_DOWN_BUTTON)) {
                this->rotateX(-CAMERA_ROTATE_SPEED);
            }
            if (context->isKeyPressed(keymap::ROTATE_CAMERA_LEFT_BUTTON)) {
                this->rotateY(-CAMERA_ROTATE_SPEED);
            }
            if (context->isKeyPressed(keymap::ROTATE_CAMERA_RIGHT_BUTTON)) {
                this->rotateY(CAMERA_ROTATE_SPEED);
            }

            if (context->isKeyPressed(keymap::MOVE_CAMERA_RIGHT_3D_BUTTON)) {
                this->moveX(CAMERA_SPEED);
            }
            if (context->isKeyPressed(keymap::MOVE_CAMERA_LEFT_3D_BUTTON)) {
                this->moveX(-CAMERA_SPEED);
            }
            if (context->isKeyPressed(keymap::MOVE_CAMERA_HIGH_BUTTON)) {
                this->moveY(-CAMERA_SPEED);
            }
            if (context->isKeyPressed(keymap::MOVE_CAMERA_LOW_BUTTON)) {
                this->moveY(CAMERA_SPEED);
            }
            if (context->isKeyPressed(keymap::MOVE_CAMERA_IN_BUTTON)) {
                this->moveForward(CAMERA_SPEED);
            }
            if (context->isKeyPressed(keymap::MOVE_CAMERA_OUT_BUTTON)) {
                this->moveForward(-CAMERA_SPEED);
            }
        }
    }
}

void Camera::setFollowMode(CameraFollowMode mode) { this->followMode = mode; }

void Camera::setTargetYCoordinates(float y) { this->targetYCoordinate = y; }

void Camera::setDesiredSize(glm::fvec2 size) { this->size = size; }

const char* Camera::getCameraBehaviour() {
    switch (this->behaviour) {
    case CAMERA_FREE:
        return "CAMERA_FREE";
    case CAMERA_ORBIT:
        return "CAMERA_ORBIT";
    case CAMERA_TPS:
        return "CAMERA_TPS";
    default:
        return "CAMERA_UNKNOWN";
    }
}

void Camera::setCameraBehaviour(CameraBehaviour behaviour) {
    switch (behaviour) {
    case CAMERA_FREE:
        this->behaviour = CAMERA_FREE;
        break;
    case CAMERA_ORBIT:
        this->behaviour = CAMERA_ORBIT;
        break;
    case CAMERA_TPS:
        this->behaviour = CAMERA_TPS;
        break;
    default:
        break;
    }
}