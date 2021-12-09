#include "../include/globalCtx.h"
#include "../include/constants.h"

GlobalCtx::GlobalCtx(GLint w, GLint h) {
    this->windowHeight = h;
    this->windowWidth = w;
    this->game = new Game();
    this->shouldDrawDebugInfo = false;
    this->bounds = glm::ivec2(0, 0);
}

GlobalCtx::~GlobalCtx() { delete this->game; }

glivec2 GlobalCtx::getWindowSize() {
    return glivec2(this->windowWidth, this->windowHeight);
}

Game* GlobalCtx::getGameRef() { return this->game; }

void GlobalCtx::updateMousePos(glm::ivec2 pos) { this->mousePos = pos; }

glm::ivec2 GlobalCtx::getMousePos() {
    return glm::ivec2(this->mousePos.x, this->mousePos.y);
}

void GlobalCtx::toggleDebugInfo() {
    this->shouldDrawDebugInfo = !this->shouldDrawDebugInfo;
}

void GlobalCtx::toggleCameraInfo() {
    this->shouldDrawCameraInfo = !this->shouldDrawCameraInfo;
}

void GlobalCtx::updateTiming(GLdouble framerate, GLdouble deltaTime) {
    this->framerate = framerate;
    this->deltaTime = deltaTime;
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

void GlobalCtx::moveBoundsX(int x) { this->bounds.x += x; }

void GlobalCtx::moveBoundsY(int y) { this->bounds.y += y; }

void GlobalCtx::idle() {
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glOrtho(-WINDOW_WIDTH + this->bounds.x, WINDOW_WIDTH + this->bounds.x,
            WINDOW_HEIGHT + this->bounds.y, -WINDOW_HEIGHT + this->bounds.y, -1,
            1);
    this->game->idle();
}

glm::ivec4 GlobalCtx::getCurrentCameraBounds() {
    return glm::ivec4(-10 + this->bounds.x, 10 + this->bounds.x,
                      10 + this->bounds.y, -10 + this->bounds.y);
}
