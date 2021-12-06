#ifndef DEBUG_H
#define DEBUG_H

#include "../include/globalCtx.h"
#include "../libs/imgui/imgui.h"
#include "../libs/imgui/imgui_impl_glut.h"
#include "../libs/imgui/imgui_impl_opengl2.h"

extern GlobalCtx* context;

namespace debug {
void imgui_init();
void drawUI();
void imgui_display();
} // namespace debug

#endif