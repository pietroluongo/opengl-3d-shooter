#ifndef DEBUG_H
#define DEBUG_H

#include "../include/globalCtx.h"
#include "../libs/imgui/imgui.h"
#ifdef USE_GLUT
#include "../libs/imgui/glut/imgui_impl_glut.h"
#endif
#ifdef USE_GLFW
#include "../libs/imgui/glfw/imgui_impl_glfw.h"
#endif
#include "../libs/imgui/imgui_impl_opengl2.h"
#include <string>
#include <vector>

extern GlobalCtx* context;

namespace debug {
void imgui_init();
void drawUI();
void imgui_display();

void drawPlayerInfo();
void drawLightingInfo();
void drawMemoryInfo();
void drawCameraInfo();
void drawPhysicsInfo();
void drawEnemyInfo();
void drawDebugInfo();

} // namespace debug

#endif