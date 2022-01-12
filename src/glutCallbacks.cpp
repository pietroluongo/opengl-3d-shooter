#include "../include/glutCallbacks.h"
#include "../include/camera.h"
#include "../include/constants.h"
#include "../include/debug.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    context->getGameRef()->draw();
    debug::drawUI();

    glutPostRedisplay();
    glutSwapBuffers();
}

void keyDown(unsigned char key, int x, int y) {
    context->updateKeyStatus(key, KEY_DOWN_STATUS);
    glutPostRedisplay();
}

void specialDown(int key, int x, int y) {
    context->updateKeyStatus(key, KEY_DOWN_STATUS);
    if (key == GLUT_KEY_F1) {
        context->toggleDebugInfo();
    }
    if (key == GLUT_KEY_F2) {
        context->toggleCameraInfo();
    }
    if (key == GLUT_KEY_F3) {
        context->togglePhysicsInfo();
    }
    if (key == GLUT_KEY_F12) {
        context->togglePlayerInfo();
    }
    if (key == GLUT_KEY_F4) {
        context->toggleEnemyInfo();
    }
    glutPostRedisplay();
}

void specialUp(int key, int x, int y) {
    context->updateKeyStatus(key, KEY_UP_STATUS);
    glutPostRedisplay();
}

void keyUp(unsigned char key, int x, int y) {
    context->updateKeyStatus(key, KEY_UP_STATUS);
    if (key == ' ') {
        context->getGameRef()->getPlayer()->shoot();
    }
    glutPostRedisplay();
}

void setupGlut(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow(WINDOW_TITLE);
    debug::imgui_init();

    glutDisplayFunc(display);
    glutPassiveMotionFunc(passiveMotion);
    glutIdleFunc(idle);

    glutKeyboardFunc(keyDown);
    glutKeyboardUpFunc(keyUp);

    glutSpecialFunc(specialDown);
    glutSpecialUpFunc(specialUp);
}

void passiveMotion(int x, int y) { context->updateMousePos(glm::ivec2(x, y)); }

void idle() {
    static GLdouble prevTime = glutGet(GLUT_ELAPSED_TIME);
    GLdouble curTime, deltaTime;
    curTime = glutGet(GLUT_ELAPSED_TIME);
    deltaTime = curTime - prevTime;
    prevTime = curTime;
    double framerate = 1.0 / deltaTime * 1000;
    context->updateTiming(framerate, deltaTime / 1000);
    context->idle();
    glutPostRedisplay();
}