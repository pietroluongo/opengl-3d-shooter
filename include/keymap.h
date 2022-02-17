#ifndef KEYMAP_H
#define KEYMAP_H

#ifdef USE_GLFW
#include <GLFW/glfw3.h>

namespace keymap {
constexpr const int MOVE_UP_BUTTON = GLFW_KEY_W;
constexpr const int MOVE_DOWN_BUTTON = GLFW_KEY_S;
constexpr const int MOVE_LEFT_BUTTON = GLFW_KEY_A;
constexpr const int MOVE_RIGHT_BUTTON = GLFW_KEY_D;

constexpr const int TOGGLE_DEBUG_INFO_BUTTON = GLFW_KEY_F1;
constexpr const int TOGGLE_CAMERA_INFO_BUTTON = GLFW_KEY_F2;
constexpr const int TOGGLE_PHYSICS_INFO_BUTTON = GLFW_KEY_F3;
constexpr const int TOGGLE_ENEMY_INFO_BUTTON = GLFW_KEY_F4;
constexpr const int TOGGLE_MEMORY_INFO_BUTTON = GLFW_KEY_F5;
constexpr const int TOGGLE_PLAYER_INFO_BUTTON = GLFW_KEY_F12;

constexpr const int CLOSE_PROGRAM_BUTTON = GLFW_KEY_ESCAPE;

constexpr const int RESTART_GAME_BUTTON = GLFW_KEY_R;
constexpr const int PAUSE_GAME_BUTTON = GLFW_KEY_P;

constexpr const int MOVE_CAMERA_LEFT_BUTTON = GLFW_KEY_J;
constexpr const int MOVE_CAMERA_RIGHT_BUTTON = GLFW_KEY_L;
constexpr const int MOVE_CAMERA_UP_BUTTON = GLFW_KEY_I;
constexpr const int MOVE_CAMERA_DOWN_BUTTON = GLFW_KEY_K;

} // namespace keymap

#else
#include <GL/freeglut.h>
namespace keymap {

constexpr const int MOVE_UP_BUTTON = 'w';
constexpr const int MOVE_DOWN_BUTTON = 's';
constexpr const int MOVE_LEFT_BUTTON = 'a';
constexpr const int MOVE_RIGHT_BUTTON = 'd';

constexpr const int TOGGLE_DEBUG_INFO_BUTTON = GLUT_KEY_F1;
constexpr const int TOGGLE_CAMERA_INFO_BUTTON = GLUT_KEY_F2;
constexpr const int TOGGLE_PHYSICS_INFO_BUTTON = GLUT_KEY_F3;
constexpr const int TOGGLE_ENEMY_INFO_BUTTON = GLUT_KEY_F4;
constexpr const int TOGGLE_MEMORY_INFO_BUTTON = GLUT_KEY_F5;
constexpr const int TOGGLE_PLAYER_INFO_BUTTON = GLUT_KEY_F12;

constexpr const int CLOSE_PROGRAM_BUTTON = 27; // ESC

constexpr const int MOVE_CAMERA_LEFT_BUTTON = 'j';
constexpr const int MOVE_CAMERA_RIGHT_BUTTON = 'l';
constexpr const int MOVE_CAMERA_UP_BUTTON = 'i';
constexpr const int MOVE_CAMERA_DOWN_BUTTON = 'k';
} // namespace keymap

#endif

#endif