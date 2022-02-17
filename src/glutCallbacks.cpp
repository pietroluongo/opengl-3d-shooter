#include "../include/glutCallbacks.h"
#include "../include/camera.h"
#include "../include/constants.h"
#include "../include/debug.h"

#include "../libs/imgui/glut/imgui_impl_glut.h"
#include "../libs/imgui/imgui.h"
#include "../libs/imgui/imgui_impl_opengl2.h"

#include <GL/gl.h>
#include <GL/glu.h>
#if defined(_WIN32) || defined(WIN32)
#include <windows.h>
#endif
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

void mouse(int button, int state, int x, int y) {
    if (context->imguiHasMouseFocus) {
        ImGui_ImplGLUT_MouseFunc(button, state, x, y);
        ImGui_ImplGLUT_MotionFunc(x, y);
        return;
    }

    if (state == GLUT_DOWN) {
        if (button == GLUT_LEFT_BUTTON) {
            context->setMouseButtons(MOUSE_BUTTON_LEFT, true);
        } else if (button == GLUT_RIGHT_BUTTON) {
            context->setMouseButtons(MOUSE_BUTTON_RIGHT, true);
        }
    } else if (state == GLUT_UP) {
        if (button == GLUT_LEFT_BUTTON) {
            context->setMouseButtons(MOUSE_BUTTON_LEFT, false);
        } else if (button == GLUT_RIGHT_BUTTON) {
            context->setMouseButtons(MOUSE_BUTTON_RIGHT, false);
        }
    }
    passiveMotion(x, y);
    glutPostRedisplay();
};

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
    if(key == GLUT_KEY_F5) {
        context->toggleMemoryInfo();
    }
    glutPostRedisplay();
}

void specialUp(int key, int x, int y) {
    context->updateKeyStatus(key, KEY_UP_STATUS);
    glutPostRedisplay();
}

void keyUp(unsigned char key, int x, int y) {
    context->updateKeyStatus(key, KEY_UP_STATUS);
    if (key == 'r') {
        context->resetGame();
    }
    if (key == 'p') {
        context->getGameRef()->togglePause();
    }
    if (key == 'm') {
        context->imguiHasMouseFocus = !context->imguiHasMouseFocus;
    }
    glutPostRedisplay();
}

void setupGlut(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow(WINDOW_TITLE);
    debug::imgui_init();
    glClearColor(0.0, 0.0, 0.0, 0.0);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    glutDisplayFunc(display);
    glutPassiveMotionFunc(passiveMotion);
    glutMotionFunc(passiveMotion);
    glutIdleFunc(idle);

    glutKeyboardFunc(keyDown);
    glutKeyboardUpFunc(keyUp);

    glutSpecialFunc(specialDown);
    glutSpecialUpFunc(specialUp);

    glutMouseFunc(mouse);
}

void passiveMotion(int x, int y) {
    if (context->imguiHasMouseFocus) {
        ImGui_ImplGLUT_MotionFunc(x, y);
        return;
    }
    context->updateMousePos(glm::ivec2(x, y));
}

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