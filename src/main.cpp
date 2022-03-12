#if defined(_WIN32) || defined(WIN32)
#define UNICODE
#include <windows.h>
#endif

#ifdef USE_GLUT
#include "../include/glutCallbacks.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#endif

#ifdef USE_GLFW
#include "../include/glfwCallbacks.h"
#include <GLFW/glfw3.h>
#endif

#include <cstdio>

#include "../include/constants.h"
#include "../include/debug.h"
#include "../include/map.h"
#include "_main.h"

#ifndef GIT_HASH
#define GIT_HASH "unknown revision"
#endif

#ifndef COMPILE_TIME
#define COMPILE_TIME "unknown time"
#endif

void init() {
    // glClearColor(0.f, 0.f, 1.f, 1.f);

    // glMatrixMode(GL_PROJECTION);
    // glOrtho(-WINDOW_WIDTH, WINDOW_WIDTH, WINDOW_HEIGHT, -WINDOW_HEIGHT, -1,
    // 1); glMatrixMode(GL_MODELVIEW); glLoadIdentity();
}

void checkParams(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: %s <arena file>\n", argv[0]);
#if defined(_WIN32) || defined(WIN32)
        MessageBox(
            NULL,
            (LPCWSTR)L"Drag a .svg map file on to the executable to load it.",
            (LPCWSTR)L"Error: No map file specified", MB_OK | MB_ICONERROR);
#endif
        exit(1);
    }
}

int main(int argc, char** argv) {
    checkParams(argc, argv);
    static const char* header =
        "\n\n########################################################## \n\
#                    2D Shooter                          # \n\
#        %s        # \n\
#        compiled at %s           # \n\
########################################################## \
            \n\n";
    printf(header, GIT_HASH, COMPILE_TIME);

    std::unique_ptr<GlobalCtx> contextPtr(
        new GlobalCtx(WINDOW_WIDTH, WINDOW_HEIGHT, argv[1]));
    context = contextPtr.get();

#ifdef USE_GLUT
    setupGlut(argc, argv);
#endif

    init();

#ifdef USE_GLUT
    glutMainLoop();
#else
    glfw::init();

    glfw::mainLoop();

    // Cleanup
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(context->getWindow());
    glfwTerminate();

#endif
    return 0;
}