#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cstdio>

#include "../include/constants.h"
#include "../include/debug.h"
#include "../include/glutCallbacks.h"
#include "../include/map.h"
#include "_main.h"

#ifndef GIT_HASH
#define GIT_HASH "unknown revision"
#endif

#ifndef COMPILE_TIME
#define COMPILE_TIME "unknown time"
#endif

void init() {
    glClearColor(0.f, 0.f, 0.f, 1.f);

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

    static const char* header =
        "\n\n########################################################## \n\
#                 Mario Shooter 2D                       # \n\
#        %s        # \n\
#        compiled at %s           # \n\
########################################################## \
            \n\n";
    printf(header, GIT_HASH, COMPILE_TIME);

    context = new GlobalCtx(WINDOW_WIDTH, WINDOW_HEIGHT);

    context->getGameRef()->getMap()->loadArena(argv[1]);

    setupGlut(argc, argv);
    init();

    glutMainLoop();

    delete (context);
    return 0;
}