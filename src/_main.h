#ifndef MAIN_H
#define MAIN_H
#include "../include/globalCtx.h"

GlobalCtx* context;

void init();
void display();
void setupGlut(int argc, char** argv);

#endif