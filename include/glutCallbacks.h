#ifndef GLUT_CALLBACKS_H
#define GLUT_CALLBACKS_H
#include "./globalCtx.h"

extern GlobalCtx* context;

void display();
void idle();
void mouse();
void passiveMotion(int x, int y);
void specialDown(int key, int x, int y);
void specialUp(int key, int x, int y);
void keyUp(unsigned char key, int x, int y);
void keyDown(unsigned char key, int x, int y);

#endif