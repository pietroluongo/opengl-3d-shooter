#ifndef GLOBAL_CTX_H
#define GLOBAL_CTX_H
#include "../include/game.h"
#include "../libs/glm/glm.hpp"
#include "customTypes.h"
#include <GL/gl.h>

class GlobalCtx {
  private:
    GLint windowWidth, windowHeight;
    Game* game;
    glm::vec2 mousePos;
    bool shouldDrawDebugInfo = false;
    int keyStatus[256] = {0};
    GLdouble framerate = 0, deltaTime = 0;

  public:
    GlobalCtx(GLint w, GLint h);
    ~GlobalCtx();
    glivec2 getWindowSize();
    Game* getGameRef();
    void updateMousePos(glm::ivec2 pos);
    glm::ivec2 getMousePos();
    void toggleDebugInfo();
    void updateTiming(GLdouble framerate, GLdouble deltaTime);
    double getFramerate();
    void updateKeyStatus(int key, int status);
    void updateKeyStatus(unsigned char key, int status);
    bool isKeyPressed(int key);
    bool isKeyPressed(unsigned char key);
    double getDeltaTime();
};

#endif