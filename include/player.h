#ifndef PLAYER_H
#define PLAYER_H
#include "../include/customTypes.h"
#include <GL/gl.h>

class Player {
    glfvec2 position = {0, 0};

  public:
    Player();
    Player(GLfloat x, GLfloat y);
    void draw();
    glfvec2 getPosition();
    void moveX(double amount);
    void moveY(double amount);
};

#endif