#include "../include/globalCtx.h"
#include "../include/constants.h"
#include <cstring>

extern GlobalCtx* context;

GlobalCtx::GlobalCtx(GLint w, GLint h, char* arenaFile) {
    context = this;
    strcpy(this->arenaFile, arenaFile);
    this->windowHeight = h;
    this->windowWidth = w;
    this->game = std::unique_ptr<Game>(new Game());
    game->getMap()->loadArena(arenaFile);
    float platDepth = game->getMap()->getWorldSize().y / 2;
    for (auto plat : this->game->getMap()->getPlatforms()) {
        plat->setDepth(platDepth);
    }
    this->game->setupCamera();
    for (auto enemy : game->getEnemies()) {
        bool isGrounded = false;
        for (auto platform : game->getMap()->getPlatforms()) {
            if (platform->getCollider()->overlaps(enemy->getCollider())) {
                isGrounded = true;
                break;
            }
        }
        if (!isGrounded) {
            enemy->teleportToGround();
        }
    }
}

GlobalCtx::~GlobalCtx() {}

glivec2 GlobalCtx::getWindowSize() {
    return glivec2(this->windowWidth, this->windowHeight);
}

Game* GlobalCtx::getGameRef() { return this->game.get(); }

void GlobalCtx::updateMousePos(glm::ivec2 pos) { this->mousePos = pos; }

glm::ivec2 GlobalCtx::getScreenSpaceMousePos() {
    return glm::ivec2(this->mousePos.x, this->mousePos.y);
}

glm::fvec2 GlobalCtx::getNormalizedMousePos() {
    return glm::fvec2((this->mousePos.x * 2) / windowWidth - 1,
                      (this->mousePos.y * 2) / windowHeight - 1);
}

glm::fvec2 GlobalCtx::getWorldSpaceMousePos() {
    glm::fvec2 cameraCenter = this->game->getMainCamera()->getPosition();
    glm::fvec4 cameraBounds = this->game->getMainCamera()->getBounds();
    float dx = std::abs(cameraBounds[0] - cameraBounds[1]) / 2;
    float dy = std::abs(cameraBounds[2] - cameraBounds[3]) / 2;
    glm::fvec2 normalizedMousePos = this->getNormalizedMousePos();
    return glm::fvec2(cameraCenter.x + normalizedMousePos.x * dx,
                      cameraCenter.y + normalizedMousePos.y * dy);
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

void GlobalCtx::toggleMemoryInfo() {
    this->shouldDrawMemoryInfo = !this->shouldDrawMemoryInfo;
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
    this->game = std::unique_ptr<Game>(new Game());
    game->getMap()->loadArena(arenaFile);
    this->game->setupCamera();
    for (auto enemy : game->getEnemies()) {
        bool isGrounded = false;
        for (auto platform : game->getMap()->getPlatforms()) {
            if (platform->getCollider()->overlaps(enemy->getCollider())) {
                isGrounded = true;
                break;
            }
        }
        if (!isGrounded) {
            enemy->teleportToGround();
        }
    }
    this->totalTime = 0;
}

void GlobalCtx::setMouseButtons(MouseButtonState button, bool status) {
    if (button == MOUSE_BUTTON_LEFT) {
        this->isPressingLMB = status;
    } else if (button == MOUSE_BUTTON_RIGHT) {
        this->isPressingRMB = status;
    }
}

void GlobalCtx::addEnemyIdleTimer(double time) {
    if (this->enemyIdleTimerQueue.size() < MAX_QUEUE_SIZE) {
        this->enemyIdleTimerQueue.push_back(time);
    } else {
        this->enemyIdleTimerQueue.pop_front();
        this->enemyIdleTimerQueue.push_back(time);
    }
}

double GlobalCtx::getAveragedEnemyIdleTimer() {
    if (this->enemyIdleTimerQueue.size() == 0) {
        return 0;
    }
    double sum = 0;
    for (auto time : this->enemyIdleTimerQueue) {
        sum += time;
    }
    return sum / this->enemyIdleTimerQueue.size();
}
