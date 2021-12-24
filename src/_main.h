#ifndef MAIN_H
#define MAIN_H
#include "../include/globalCtx.h"

GlobalCtx* context;

void setupGlut(int argc, char** argv);
void init();
void loadArena(char* file);
#endif