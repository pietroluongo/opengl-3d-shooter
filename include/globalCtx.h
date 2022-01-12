#ifndef GLOBAL_CTX_H
#define GLOBAL_CTX_H
#include "../include/game.h"
#include "../libs/glm/glm.hpp"
#include "customTypes.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

class GlobalCtx {
  private:
    GLint windowWidth, windowHeight;
    Game* game;
    glm::vec2 mousePos;
    int keyStatus[256] = {0};
    GLdouble framerate = 0, deltaTime = 0;

  public:
    bool shouldDrawDebugInfo = true;
    bool shouldDrawCameraInfo = true;
    bool shouldDrawPhysicsInfo = true;
    bool shouldDrawPlayerInfo = true;

    bool shouldObjectsDrawCoordinateSystem = false;
    bool shouldObjectsDrawColliders = false;
    bool shouldPlatformsShowCollisions = false;

    void* font = GLUT_BITMAP_9_BY_15;
    char textBuffer[1024];

    GlobalCtx(GLint w, GLint h);
    ~GlobalCtx();
    bool isKeyPressed(int key);
    bool isKeyPressed(unsigned char key);
    double getDeltaTime();
    double getFramerate();
    Game* getGameRef();
    glivec2 getWindowSize();
    glm::ivec2 getScreenSpaceMousePos();
    glm::fvec2 getWorldSpaceMousePos();
    glm::fvec2 getNormalizedMousePos();
    void idle();
    void toggleDebugInfo();
    void toggleCameraInfo();
    void togglePhysicsInfo();
    void togglePlayerInfo();
    void updateKeyStatus(int key, int status);
    void updateKeyStatus(unsigned char key, int status);
    void updateMousePos(glm::ivec2 pos);
    void updateTiming(GLdouble framerate, GLdouble deltaTime);
};

#endif