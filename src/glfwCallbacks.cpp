#include "../include/glfwCallbacks.h"
#include "../include/constants.h"
#include "../include/debug.h"
#include "../include/globalCtx.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdio>

extern GlobalCtx* context;

namespace glfw {

static void glfw_error_callback(int error, const char* description) {
    printf("GLFW Error %d: %s\n", error, description);
}

static void cursorCallback(GLFWwindow* window, double xpos, double ypos) {
    context->updateMousePos(glm::ivec2(xpos, ypos));
}

static void mouseButtonCallback(GLFWwindow* window, int button, int action,
                                int mods) {
    if (action == GLFW_PRESS) {
        if (button == GLFW_MOUSE_BUTTON_LEFT) {
            context->setMouseButtons(MOUSE_BUTTON_LEFT, true);
        } else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
            context->setMouseButtons(MOUSE_BUTTON_RIGHT, true);
        }
    } else if (action == GLFW_RELEASE) {
        if (button == GLFW_MOUSE_BUTTON_LEFT) {
            context->setMouseButtons(MOUSE_BUTTON_LEFT, false);
        } else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
            context->setMouseButtons(MOUSE_BUTTON_RIGHT, false);
        }
    }
}

static void keyCallback(GLFWwindow* window, int key, int scancode, int action,
                        int mods) {
    if (action == GLFW_PRESS) {
        context->updateKeyStatus(key, KEY_DOWN_STATUS);

        if (key == GLFW_KEY_F1) {
            context->toggleDebugInfo();
        }
        if (key == GLFW_KEY_F2) {
            context->toggleCameraInfo();
        }
        if (key == GLFW_KEY_F3) {
            context->togglePhysicsInfo();
        }
        if (key == GLFW_KEY_F12) {
            context->togglePlayerInfo();
        }
        if (key == GLFW_KEY_F4) {
            context->toggleEnemyInfo();
        }
    } else if (action == GLFW_RELEASE) {
        context->updateKeyStatus(key, KEY_UP_STATUS);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    context->getGameRef()->draw();
    debug::drawUI();

    glfwSwapBuffers(context->getWindow());
}

void idle() {
    static double prevTime = glfwGetTime();
    double curTime, deltaTime;
    curTime = glfwGetTime();
    deltaTime = curTime - prevTime;
    prevTime = curTime;
    double framerate = 1.0 / deltaTime * 1000;
    context->updateTiming(framerate, deltaTime);

    processInput(context->getWindow());
    context->idle();
    display();
}

void processInput(GLFWwindow* window) {}

void init() {
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) {
        printf("Error initializing GLFW\n");
        exit(1);
    }
    GLFWwindow* mainWindow =
        glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "2D Shooter", NULL, NULL);
    if (mainWindow == NULL) {
        exit(1);
    }

    context->setWindow(mainWindow);

    glfwMakeContextCurrent(mainWindow);
    glfwSwapInterval(1);

    glfwSetCursorPosCallback(mainWindow, cursorCallback);
    glfwSetMouseButtonCallback(mainWindow, mouseButtonCallback);
    glfwSetKeyCallback(mainWindow, keyCallback);

    debug::imgui_init();

    glClearColor(0.0, 0.0, 0.0, 0.0);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
}

void mainLoop() {
    while (!glfwWindowShouldClose(context->getWindow())) {
        glfwPollEvents();
        idle();
    }
}

} // namespace glfw
