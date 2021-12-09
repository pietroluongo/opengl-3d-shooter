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
    glOrtho(-10, 10, 10, -10, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyDown(unsigned char key, int x, int y) {
    context->updateKeyStatus(key, KEY_DOWN_STATUS);
    // switch (key) {
    // case 'a':
    // case 'A':
    //     context->updateKeyStatus('a', KEY_DOWN_STATUS);
    //     break;
    // case 'd':
    // case 'D':
    //     context->updateKeyStatus('d', KEY_DOWN_STATUS);
    //     break;
    // case 'w':
    // case 'W':
    //     context->updateKeyStatus('w', KEY_DOWN_STATUS);
    //     break;
    // case 's':
    // case 'S':
    //     context->updateKeyStatus('s', KEY_DOWN_STATUS);
    //     break;
    // default:
    //     break;
    // }
    glutPostRedisplay();
}

void keyUp(unsigned char key, int x, int y) {
    context->updateKeyStatus(key, KEY_UP_STATUS);
    glutPostRedisplay();
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
    glutIdleFunc(idle);
    glutKeyboardFunc(keyDown);
    glutKeyboardUpFunc(keyUp);
}

void passiveMotion(int x, int y) { context->updateMousePos(glm::ivec2(x, y)); }

void specialFunc(int key, int x, int y) {
    // switch (key) {
    // case GLUT_KEY_F1:
    //     context->toggleDebugInfo();
    //     break;
    // }
}

void idle() {
    static GLdouble prevTime = glutGet(GLUT_ELAPSED_TIME);
    GLdouble curTime, deltaTime;
    curTime = glutGet(GLUT_ELAPSED_TIME);
    deltaTime = curTime - prevTime;
    prevTime = curTime;
    double framerate = 1.0 / deltaTime * 1000;
    context->updateTiming(framerate, deltaTime / 1000);

    if (context->isKeyPressed('d') || context->isKeyPressed('D')) {
        context->getGameRef()->getPlayer()->moveX(1);
    }
    if (context->isKeyPressed('D') || context->isKeyPressed('a')) {
        context->getGameRef()->getPlayer()->moveX(-1);
    }

    if (context->isKeyPressed('w') || context->isKeyPressed('W')) {
        context->getGameRef()->getPlayer()->moveY(-1);
    }

    if (context->isKeyPressed('s') || context->isKeyPressed('S')) {
        context->getGameRef()->getPlayer()->moveY(1);
    }

    glutPostRedisplay();
}

int main(int argc, char** argv) {
    context = new GlobalCtx(WINDOW_WIDTH, WINDOW_HEIGHT);

    setupGlut(argc, argv);
    glutMainLoop();

    delete (context);
    return 0;
}