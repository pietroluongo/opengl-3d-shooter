#ifndef DEBUG_H
#define DEBUG_H

#include "../libs/imgui/imgui.h"
#include "../libs/imgui/imgui_impl_glut.h"
#include "../libs/imgui/imgui_impl_opengl2.h"
#include "../include/globalCtx.h"


namespace debug {
    GlobalCtx* context;
    void imgui_init(GlobalCtx* context);
    void drawUI();
    void imgui_display();
}


#endif