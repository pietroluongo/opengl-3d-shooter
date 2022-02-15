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

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    debug::drawUI();

    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(0.0f, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex2f(0.5f, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex2f(0.0f, 0.5f);
    glEnd();

    context->getGameRef()->draw();

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
