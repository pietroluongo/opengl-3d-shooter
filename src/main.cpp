#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cstdio>

#include "../include/constants.h"
#include "../include/debug.h"
#include "_main.h"

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    debug::drawUI();
    context->getGameRef()->draw();
    glutPostRedisplay();
    glutSwapBuffers();
}

void init() {
    glClearColor(0.f, 0.f, 0.f, 1.f);

    glMatrixMode(GL_PROJECTION);
    glOrtho(-1, 1, 1, -1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void setupGlut(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow(WINDOW_TITLE);
    init();
    debug::imgui_init();

    glutDisplayFunc(display);
    glutPassiveMotionFunc(passiveMotion);
    glutSpecialFunc(specialFunc);
}

void passiveMotion(int x, int y) { context->updateMousePos(glm::ivec2(x, y)); }

void specialFunc(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_F1:
        context->toggleDebugInfo();
        break;
    }
}

int main(int argc, char** argv) {
    context = new GlobalCtx(WINDOW_WIDTH, WINDOW_HEIGHT);

    setupGlut(argc, argv);
    glutMainLoop();

    delete (context);
    return 0;
}