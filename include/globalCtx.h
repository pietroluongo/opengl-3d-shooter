#ifndef GLOBAL_CTX_H
#define GLOBAL_CTX_H
#include "../include/game.h"
#include "../libs/glm/glm.hpp"
#include "customTypes.h"
#include <GL/gl.h>

class GlobalCtx {
    GLint windowWidth, windowHeight;
    Game* game;

  public:
    GlobalCtx(GLint w, GLint h);
    ~GlobalCtx();
    glivec2 getWindowSize();
    Game* getGameRef();
};

#endif