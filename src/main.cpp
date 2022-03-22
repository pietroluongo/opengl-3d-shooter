#if defined(_WIN32) || defined(WIN32)
#define UNICODE
#include <cstdint>
#include <fcntl.h>
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

#if defined(_WIN32) || defined(WIN32)
    AllocConsole();

    HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
    int hCrt = _open_osfhandle((unsigned long long)handle_out, _O_TEXT);
    FILE* hf_out = _fdopen(hCrt, "w");
    setvbuf(hf_out, NULL, _IONBF, 1);
    *stdout = *hf_out;

    HANDLE handle_in = GetStdHandle(STD_INPUT_HANDLE);
    hCrt = _open_osfhandle((unsigned long long)handle_in, _O_TEXT);
    FILE* hf_in = _fdopen(hCrt, "r");
    setvbuf(hf_in, NULL, _IONBF, 128);
    *stdin = *hf_in;
#endif

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
    context->loadTexture("./assets/default.bmp");
    context->loadTexture("./assets/grass.bmp");
    context->loadTexture("./assets/floor.bmp");
    context->loadTexture("./assets/head.bmp");
    context->loadTexture("./assets/wall.bmp");
    context->loadTexture("./assets/skybox_day/back_sky_day.bmp");
    context->loadTexture("./assets/skybox_day/front_sky_day.bmp");
    context->loadTexture("./assets/skybox_day/left_sky_day.bmp");
    context->loadTexture("./assets/skybox_day/right_sky_day.bmp");
    context->loadTexture("./assets/skybox_day/top_sky_day.bmp");
    context->loadTexture("./assets/skybox_day/bottom_sky_day.bmp");

    context->loadTexture("./assets/skybox_night/back_sky_night.bmp");
    context->loadTexture("./assets/skybox_night/front_sky_night.bmp");
    context->loadTexture("./assets/skybox_night/left_sky_night.bmp");
    context->loadTexture("./assets/skybox_night/right_sky_night.bmp");
    context->loadTexture("./assets/skybox_night/top_sky_night.bmp");
    context->loadTexture("./assets/skybox_night/bottom_sky_night.bmp");

    context->debugTextures();
    context->postInit();
    glutMainLoop();

#else
    glfw::init();
    context->loadTexture("./assets/default.bmp");
    context->loadTexture("./assets/grass.bmp");
    context->loadTexture("./assets/floor.bmp");
    context->loadTexture("./assets/head.bmp");
    context->loadTexture("./assets/wall.bmp");
    context->loadTexture("./assets/skybox/back_sky.bmp");
    context->loadTexture("./assets/skybox/front_sky.bmp");
    context->loadTexture("./assets/skybox/left_sky.bmp");
    context->loadTexture("./assets/skybox/right_sky.bmp");
    context->loadTexture("./assets/skybox/top_sky.bmp");
    context->loadTexture("./assets/skybox/bottom_sky.bmp");
    context->debugTextures();
    context->postInit();
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