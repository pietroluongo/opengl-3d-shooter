#ifndef PLAYER_H
#define PLAYER_H
#include "../include/customTypes.h"
#include <GL/gl.h>

class Player {
  private:
    glfvec2 position = {0, 0};
    GLfloat size = 0;
    void handleMovementKeys();

  public:
    Player(GLfloat x, GLfloat y, GLfloat size);
    void draw();
    glfvec2 getPosition();
    void moveX(double amount);
    void moveY(double amount);
    void idle();
};

#endif