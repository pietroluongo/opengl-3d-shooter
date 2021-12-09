#include "../include/globalCtx.h"

GlobalCtx::GlobalCtx(GLint w, GLint h) {
    this->windowHeight = h;
    this->windowWidth = w;
    this->game = new Game();
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