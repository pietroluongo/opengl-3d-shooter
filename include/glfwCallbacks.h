#ifndef GLFW_CALLBACKS_H
#define GLFW_CALLBACKS_H

#include "GLFW/glfw3.h"

namespace glfw {
void display();
void idle();
void processInput(GLFWwindow* window);
void init();
void mainLoop();

} // namespace glfw

#endif