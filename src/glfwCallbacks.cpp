#include "../include/glfwCallbacks.h"
#include "../include/constants.h"
#include "../include/debug.h"
#include "../include/globalCtx.h"
#include "../include/keymap.h"
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

        switch (key) {
        case keymap::CLOSE_PROGRAM_BUTTON:
            glfwSetWindowShouldClose(window, true);
            break;
        case keymap::TOGGLE_DEBUG_INFO_BUTTON:
            context->toggleDebugInfo();
            break;
        case keymap::TOGGLE_CAMERA_INFO_BUTTON:
            context->toggleCameraInfo();
            break;
        case keymap::TOGGLE_PHYSICS_INFO_BUTTON:
            context->togglePhysicsInfo();
            break;
        case keymap::TOGGLE_ENEMY_INFO_BUTTON:
            context->toggleEnemyInfo();
            break;
        case keymap::TOGGLE_MEMORY_INFO_BUTTON:
            context->toggleMemoryInfo();
            break;
        case keymap::TOGGLE_PLAYER_INFO_BUTTON:
            context->togglePlayerInfo();
            break;
        case keymap::PAUSE_GAME_BUTTON:
            context->getGameRef()->togglePause();
            break;
        case keymap::RESTART_GAME_BUTTON:
            context->resetGame();
            break;
        default:
            break;
        }
    } else if (action == GLFW_RELEASE) {
        context->updateKeyStatus(key, KEY_UP_STATUS);
    }
}

void display() {
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

    context->axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &context->nAxes);

    processInput(context->getWindow());
    context->idle();
    auto error = glGetError();
    while (error != GL_NO_ERROR) {
        printf("OpenGL Error: %d\n", error);
        error = glGetError();
    }
}

void processInput(GLFWwindow* window) {}

void resizeCallback(GLFWwindow* window, int x, int y) {
    context->setWindowSize({x, y});
}

void init() {
    glClearColor(0.f, 0.f, 1.f, 1.f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

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

    glfwSetWindowPos(mainWindow, -1920 + 500, 40);

    glfwMakeContextCurrent(mainWindow);
    glfwSwapInterval(1);

    glfwSetCursorPosCallback(mainWindow, cursorCallback);
    glfwSetMouseButtonCallback(mainWindow, mouseButtonCallback);
    glfwSetKeyCallback(mainWindow, keyCallback);
    glfwSetFramebufferSizeCallback(mainWindow, resizeCallback);
    glfwSetWindowSizeLimits(mainWindow, 500, 500, GLFW_DONT_CARE,
                            GLFW_DONT_CARE);

    debug::imgui_init();

    glClearColor(0.0, 0.0, 1.0, 0.0);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_SMOOTH);

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

    int hasJoystick = glfwJoystickPresent(GLFW_JOYSTICK_1);
    if (hasJoystick) {
        printf("Joystick detected\n");
    } else {
        printf("No joystick detected\n");
    }

    auto error = glGetError();
    if (error != GL_NO_ERROR) {
        printf("Error initializing OpenGL! %d\n", error);
        exit(1);
    }
}

void mainLoop() {
    while (!glfwWindowShouldClose(context->getWindow())) {
        glfwPollEvents();
        idle();
        display();
    }
}

} // namespace glfw
