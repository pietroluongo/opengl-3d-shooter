#ifndef MAIN_H
#define MAIN_H
#include "../include/globalCtx.h"

GlobalCtx* context;

void setupGlut(int argc, char** argv);

void init();
void display();
void idle();
void mouse();
void passiveMotion(int x, int y);
void specialFunc(int key, int x, int y);
void keyUp(unsigned char key, int x, int y);
void keyDown(unsigned char key, int x, int y);

#endif