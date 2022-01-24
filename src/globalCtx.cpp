#include "../include/globalCtx.h"
#include "../include/constants.h"
#include <cstring>

extern GlobalCtx* context;

GlobalCtx::GlobalCtx(GLint w, GLint h, char* arenaFile) {
    context = this;
    strcpy(this->arenaFile, arenaFile);
    this->windowHeight = h;
    this->windowWidth = w;
    this->game = new Game();
    game->getMap()->loadArena(arenaFile);
}

GlobalCtx::~GlobalCtx() { delete (this->game); }

glivec2 GlobalCtx::getWindowSize() {
    return glivec2(this->windowWidth, this->windowHeight);
}

Game* GlobalCtx::getGameRef() { return this->game; }

void GlobalCtx::updateMousePos(glm::ivec2 pos) { this->mousePos = pos; }

glm::ivec2 GlobalCtx::getScreenSpaceMousePos() {
    return glm::ivec2(this->mousePos.x, this->mousePos.y);
}

glm::fvec2 GlobalCtx::getNormalizedMousePos() {
    return glm::fvec2((this->mousePos.x * 2) / WINDOW_WIDTH - 1,
                      (this->mousePos.y * 2) / WINDOW_HEIGHT - 1);
}

glm::fvec2 GlobalCtx::getWorldSpaceMousePos() {
    glm::fvec2 cameraCenter = this->game->getMainCamera()->getPosition();
    glm::fvec2 normalizedMousePos = this->getNormalizedMousePos();
    return glm::fvec2(cameraCenter.x + normalizedMousePos.x * WINDOW_WIDTH,
                      cameraCenter.y + normalizedMousePos.y * WINDOW_HEIGHT);
}

void GlobalCtx::toggleDebugInfo() {
    this->shouldDrawDebugInfo = !this->shouldDrawDebugInfo;
}

void GlobalCtx::toggleCameraInfo() {
    this->shouldDrawCameraInfo = !this->shouldDrawCameraInfo;
}

void GlobalCtx::togglePhysicsInfo() {
    this->shouldDrawPhysicsInfo = !this->shouldDrawPhysicsInfo;
}

void GlobalCtx::togglePlayerInfo() {
    this->shouldDrawPlayerInfo = !this->shouldDrawPlayerInfo;
}

void GlobalCtx::toggleEnemyInfo() {
    this->shouldDrawEnemyInfo = !this->shouldDrawEnemyInfo;
}

void GlobalCtx::updateTiming(GLdouble framerate, GLdouble deltaTime) {
    this->framerate = framerate;
    this->deltaTime = deltaTime;
    this->totalTime += deltaTime;
}

double GlobalCtx::getFramerate() { return this->framerate; }

void GlobalCtx::updateKeyStatus(int key, int status) {
    this->keyStatus[key] = status;
}

void GlobalCtx::updateKeyStatus(unsigned char key, int status) {
    this->updateKeyStatus((int)key, status);
}

bool GlobalCtx::isKeyPressed(int key) {
    return this->keyStatus[key] == KEY_DOWN_STATUS;
}

bool GlobalCtx::isKeyPressed(unsigned char key) {
    return this->isKeyPressed((int)key);
}

double GlobalCtx::getDeltaTime() { return this->deltaTime; }

void GlobalCtx::idle() { this->game->idle(); }

double GlobalCtx::getTotalPlaytime() { return this->totalTime; }

void GlobalCtx::resetGame() {
    if (!this->game->canRestart())
        return;
    delete (this->game);
    this->game = new Game();
    game->getMap()->loadArena(arenaFile);

    this->totalTime = 0;
}