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
    int keyStatus[256] = {0};
    GLdouble framerate = 0, deltaTime = 0;

  public:
    bool shouldDrawDebugInfo = false;
    bool shouldDrawCameraInfo = false;
    bool shouldDrawPhysicsInfo = false;

    bool shouldObjectsDrawCoordinateSystem = false;


    GlobalCtx(GLint w, GLint h);
    ~GlobalCtx();
    bool isKeyPressed(int key);
    bool isKeyPressed(unsigned char key);
    double getDeltaTime();
    double getFramerate();
    Game* getGameRef();
    glivec2 getWindowSize();
    glm::ivec2 getMousePos();
    void idle();
    void toggleDebugInfo();
    void toggleCameraInfo();
    void togglePhysicsInfo();
    void updateKeyStatus(int key, int status);
    void updateKeyStatus(unsigned char key, int status);
    void updateMousePos(glm::ivec2 pos);
    void updateTiming(GLdouble framerate, GLdouble deltaTime);
};

#endif