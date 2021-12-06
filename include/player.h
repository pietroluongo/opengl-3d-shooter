#ifndef PLAYER_H
#define PLAYER_H
#include <GL/gl.h>
#include "../include/customTypes.h"

class Player {
    glfvec2 position = {0, 0};
    public:
        Player();
        Player(GLfloat x, GLfloat y);
        void draw();
        glfvec2 getPosition();
};

#endif