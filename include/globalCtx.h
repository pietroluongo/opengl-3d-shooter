#ifndef GLOBAL_CTX_H
#define GLOBAL_CTX_H
#include "../include/game.h"
#include "../libs/glm/glm.hpp"
#include "customTypes.h"
#include <deque>
#include <map>

#if defined(_WIN32) || defined(WIN32)
#include <windows.h>
#endif

#ifdef USE_GLUT
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#ifdef USE_GLFW
#include <GLFW/glfw3.h>
#endif

enum MouseButtonState {
    MOUSE_BUTTON_LEFT,
    MOUSE_BUTTON_RIGHT,
};

constexpr unsigned long int MAX_QUEUE_SIZE = 100;

class GlobalCtx {
  private:
    GLint windowWidth, windowHeight;
    std::unique_ptr<Game> game;
    glm::vec2 mousePos;
    int keyStatus[1024] = {0};
    bool isPressingLMB = false;
    bool isPressingRMB = false;
    GLdouble framerate = 0, deltaTime = 0;
    GLdouble totalTime = 0;
    char arenaFile[99] = {};

    // timers
    double playerIdleTime;
    double projectileIdleTime;

    std::map<std::string, GLuint> textureMap;

#ifdef USE_GLFW
    GLFWwindow* window;
#endif

  public:
    std::deque<double> enemyIdleTimerQueue;

    bool shouldDrawDebugInfo = false;
    bool shouldDrawCameraInfo = false;
    bool shouldDrawPhysicsInfo = false;
    bool shouldDrawPlayerInfo = false;
    bool shouldDrawEnemyInfo = false;
    bool shouldDrawMemoryInfo = false;
    bool shouldDrawLightingInfo = false;

    bool shouldObjectsDrawCoordinateSystem = false;
    bool shouldObjectsDrawColliders = false;
    bool shouldPlatformsShowCollisions = false;
    bool shouldEnemiesDrawInfo = false;

    bool enemiesCanShoot = true;
    bool enemiesCanMove = true;

    bool imguiHasMouseFocus = false;

    bool userHasJoystick = false;

    int nAxes = 0;
    const float* axes;

#ifdef USE_GLUT
    void* font = GLUT_BITMAP_9_BY_15;
#endif
    char textBuffer[1024];

    GlobalCtx(GLint w, GLint h, char* arenaFile);
    ~GlobalCtx();
    bool isKeyPressed(int key);
    bool isKeyPressed(unsigned char key);
    double getDeltaTime();
    double getFramerate();
    Game* getGameRef();
    glivec2 getWindowSize();
    void setWindowSize(glivec2 size) {
        this->windowWidth = size.x;
        this->windowHeight = size.y;
    }
    glm::ivec2 getScreenSpaceMousePos();
    glm::fvec2 getWorldSpaceMousePos();
    glm::fvec2 getNormalizedMousePos();
    double getTotalPlaytime();
    void idle();
    void toggleDebugInfo();
    void toggleCameraInfo();
    void toggleEnemyInfo();
    void togglePhysicsInfo();
    void togglePlayerInfo();
    void toggleMemoryInfo();
    void toggleLightingInfo();
    void updateKeyStatus(int key, int status);
    void updateKeyStatus(unsigned char key, int status);
    void updateMousePos(glm::ivec2 pos);
    void updateTiming(GLdouble framerate, GLdouble deltaTime);
    void resetGame();
    void setMouseButtons(MouseButtonState state, bool status);
    bool getIsPressingLMB() const { return this->isPressingLMB; }
    bool getIsPressingRMB() const { return this->isPressingRMB; }
    void addEnemyIdleTimer(double time);
    double getAveragedEnemyIdleTimer();
    void loadTexture(const char* path);
    GLuint getTexture(const char* id) { return this->textureMap[id]; }
    void debugTextures();
    void postInit();
#ifdef USE_GLFW
    GLFWwindow* getWindow() { return this->window; }
    void setWindow(GLFWwindow* window) { this->window = window; }
#endif
};

#endif