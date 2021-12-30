#ifndef CONSTANTS_H
#define CONSTANTS_H

constexpr const int WINDOW_WIDTH = 1000;
constexpr const int WINDOW_HEIGHT = 1000;

constexpr const char* WINDOW_TITLE = "trabalhocg";

constexpr const char MOVE_UP = 'w';
constexpr const char MOVE_DOWN = 's';
constexpr const char MOVE_LEFT = 'a';
constexpr const char MOVE_RIGHT = 'd';

enum keyStatus { KEY_UP_STATUS, KEY_DOWN_STATUS };

constexpr const char* SVG_BARRIER = "black";
constexpr const char* SVG_PLAYABLE_AREA = "blue";
constexpr const char* SVG_ENEMY = "red";
constexpr const char* SVG_PLAYER = "green";

#endif