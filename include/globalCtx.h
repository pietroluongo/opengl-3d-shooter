#ifndef GLOBAL_CTX_H
#define GLOBAL_CTX_H
#include <GL/gl.h>
#include "../libs/glm/glm.hpp"
#include "customTypes.h"
#include "../include/game.h"

class GlobalCtx
{
    GLint windowWidth, windowHeight;
    Game* game;
    public:
        GlobalCtx(GLint w, GLint h);
        ~GlobalCtx();
        glivec2 getWindowSize();
        Game* getGameRef();
};

#endif