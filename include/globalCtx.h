#ifndef GLOBAL_CTX_H
#define GLOBAL_CTX_H
#include <GL/gl.h>
#include "../libs/glm/glm.hpp"
#include "customTypes.h"

class GlobalCtx
{
    GLint windowWidth, windowHeight;
    public:
        GlobalCtx(GLint w, GLint h);
        glivec2 getWindowSize();
};

#endif