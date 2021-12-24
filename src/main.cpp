#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cstdio>

#include "../include/constants.h"
#include "../include/debug.h"
#include "../include/glutCallbacks.h"
#include "_main.h"

void init() {
    glClearColor(0.f, 0.f, 0.f, 1.f);

    glMatrixMode(GL_PROJECTION);
    glOrtho(-WINDOW_WIDTH, WINDOW_WIDTH, WINDOW_HEIGHT, -WINDOW_HEIGHT, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv) {
    context = new GlobalCtx(WINDOW_WIDTH, WINDOW_HEIGHT);
    static const char* header =
        "########################################################## \n\
#                 Mario Shooter 2D                       # \n\
#        %s        # \n\
#        compiled at %s           # \n\
########################################################## \
            \n";
    printf(header, GIT_HASH, COMPILE_TIME);
    setupGlut(argc, argv);
    init();

    glutMainLoop();

    delete (context);
    return 0;
}