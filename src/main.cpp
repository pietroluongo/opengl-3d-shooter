#if defined(_WIN32) || defined(WIN32)
#define UNICODE
#include <windows.h>
#endif

#ifdef USE_GLUT
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#ifdef USE_GLFW
#include <GLFW/glfw3.h>
#endif

#include <cstdio>

#include "../include/constants.h"
#include "../include/debug.h"
#ifdef USE_GLUT
#include "../include/glutCallbacks.h"
#endif
#include "../include/map.h"
#include "_main.h"

#ifndef GIT_HASH
#define GIT_HASH "unknown revision"
#endif

#ifndef COMPILE_TIME
#define COMPILE_TIME "unknown time"
#endif

static void glfw_error_callback(int error, const char* description) {
    printf("GLFW Error %d: %s\n", error, description);
}

void init() {
    glClearColor(0.f, 0.f, 1.f, 1.f);

    glMatrixMode(GL_PROJECTION);
    glOrtho(-WINDOW_WIDTH, WINDOW_WIDTH, WINDOW_HEIGHT, -WINDOW_HEIGHT, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: %s <arena file>\n", argv[0]);
        return 1;
    }

    //     static const char* header =
    //         "\n\n##########################################################
    //         \n\
// #                 2D Shooter                             # \n\
// #        %s        # \n\
// #        compiled at %s           # \n\
// ########################################################## \
//             \n\n";
    static const char* header =
        "\n\n########################################################## \n\
#                    2D Shooter                          # \n\
#        %s        # \n\
#        compiled at %s           # \n\
########################################################## \
            \n\n";
    printf(header, GIT_HASH, COMPILE_TIME);

    context = new GlobalCtx(WINDOW_WIDTH, WINDOW_HEIGHT, argv[1]);

#ifdef USE_GLUT
    setupGlut(argc, argv);
#endif

    init();

#ifdef USE_GLFW

    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) {
        return 1;
    }
    GLFWwindow* mainWindow =
        glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "2D Shooter", NULL, NULL);
    if (mainWindow == NULL) {
        return 1;
    }
    glfwMakeContextCurrent(mainWindow);
    glfwSwapInterval(1);

    while (!glfwWindowShouldClose(mainWindow)) {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(mainWindow);
    }

#endif

#ifdef USE_GLUT
    glutMainLoop();
#endif

    delete (context);
    return 0;
}