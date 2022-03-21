#ifndef KEYMAP_H
#define KEYMAP_H

#ifdef USE_GLFW
#include <GLFW/glfw3.h>

namespace keymap {
constexpr const int MOVE_UP_BUTTON = GLFW_KEY_W;
constexpr const int MOVE_DOWN_BUTTON = GLFW_KEY_S;
constexpr const int MOVE_LEFT_BUTTON = GLFW_KEY_A;
constexpr const int MOVE_RIGHT_BUTTON = GLFW_KEY_D;

constexpr const int JUMP_BUTTON = GLFW_KEY_SPACE;

constexpr const int MOVE_FORWARD_BUTTON = GLFW_KEY_W;
constexpr const int MOVE_BACKWARD_BUTTON = GLFW_KEY_S;

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

constexpr const int ROTATE_CAMERA_LEFT_BUTTON = GLFW_KEY_J;
constexpr const int ROTATE_CAMERA_RIGHT_BUTTON = GLFW_KEY_L;
constexpr const int ROTATE_CAMERA_UP_BUTTON = GLFW_KEY_I;
constexpr const int ROTATE_CAMERA_DOWN_BUTTON = GLFW_KEY_K;

constexpr const int MOVE_CAMERA_IN_BUTTON = GLFW_KEY_T;
constexpr const int MOVE_CAMERA_OUT_BUTTON = GLFW_KEY_G;
constexpr const int MOVE_CAMERA_HIGH_BUTTON = GLFW_KEY_Y;
constexpr const int MOVE_CAMERA_LOW_BUTTON = GLFW_KEY_R;

constexpr const int MOVE_CAMERA_RIGHT_3D_BUTTON = GLFW_KEY_H;
constexpr const int MOVE_CAMERA_LEFT_3D_BUTTON = GLFW_KEY_F;

constexpr const int CAMERA_SET_FPS = GLFW_KEY_1;
constexpr const int CAMERA_SET_AIM = GLFW_KEY_2;
constexpr const int CAMERA_SET_THIRD_PERSON = GLFW_KEY_3;
constexpr const int CAMERA_TOGGLE_ORBIT = GLFW_KEY_X;

constexpr const int CAMERA_ZOOM_INCREASE = GLFW_KEY_EQUAL;
constexpr const int CAMERA_ZOOM_DECREASE = GLFW_KEY_MINUS;

constexpr const int CAMERA_TOGGLE_AIM_SECONDARY = GLFW_MOUSE_BUTTON_2;

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
constexpr const int ROTATE_CAMERA_UP_BUTTON = 'i';
constexpr const int ROTATE_CAMERA_DOWN_BUTTON = 'k';
constexpr const int ROTATE_CAMERA_LEFT_BUTTON = 'j';
constexpr const int ROTATE_CAMERA_RIGHT_BUTTON = 'l';
constexpr const int MOVE_CAMERA_RIGHT_3D_BUTTON = 'h';
constexpr const int MOVE_CAMERA_LEFT_3D_BUTTON = 'f';
constexpr const int JUMP_BUTTON = ' ';

constexpr const int MOVE_FORWARD_BUTTON = 'w';
constexpr const int MOVE_BACKWARD_BUTTON = 's';

constexpr const int MOVE_CAMERA_IN_BUTTON = 't';
constexpr const int MOVE_CAMERA_OUT_BUTTON = 'g';
constexpr const int MOVE_CAMERA_HIGH_BUTTON = 'y';
constexpr const int MOVE_CAMERA_LOW_BUTTON = 'r';
constexpr const int CAMERA_TOGGLE_ORBIT = 'x';

constexpr const int CAMERA_SET_FPS = '1';
constexpr const int CAMERA_SET_AIM = '2';
constexpr const int CAMERA_SET_THIRD_PERSON = '3';

constexpr const int TOGGLE_NIGHT_MODE = 'n';

} // namespace keymap

#endif

#endif