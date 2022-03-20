#include "../include/game.h"
#include "../include/globalCtx.h"
#include "../include/lightSrc.h"
#include "../libs/glm/gtc/type_ptr.hpp"
#include <algorithm>
#include <chrono>
#include <cstring>
#include <memory>

extern GlobalCtx* context;

Game::Game() {
    this->player = nullptr;
    this->map = std::unique_ptr<Map>(new Map());
    this->cam = std::unique_ptr<Camera>(new Camera(CameraMode::CAMERA_3D));
    this->cam->setFollowMode(CAMERA_FOLLOW_MODE_SINGLE_AXIS);
}

Game::~Game() {}

glfvec3 Game::getPlayerPosition() { return this->player->getPosition(); }

void Game::draw() {
    this->cam->idle();
    this->map->draw();
    this->player->draw();
    for (auto& enemy : this->enemies) {
        enemy->draw();
    }
    for (auto& projectile : this->projectiles) {
        projectile->draw();
    }
    if (this->state == GameState::OVER) {
        this->drawGameOverScreen();
    } else if (this->state == GameState::WON) {
        this->drawWinScreen();
    }

    {
        glm::fvec3 playerPos = this->map->getWorldCenter();
        glLightfv(GL_LIGHT0, GL_POSITION,
                  glm::value_ptr(
                      glm::fvec4(playerPos.x, playerPos.y, playerPos.z, 1.0)));
        glLightfv(GL_LIGHT0, GL_DIFFUSE,
                  glm::value_ptr(glm::fvec3(1.0f, 1.0f, 1.0f)));
    }
}

Player* Game::getPlayer() { return this->player.get(); }

void Game::idle() {
    if (this->state == GameState::PLAYING) {
        std::chrono::duration<double, std::milli> elapsed;
        auto measurementStart = std::chrono::high_resolution_clock::now();
        this->player->idle();
        elapsed = std::chrono::high_resolution_clock::now() - measurementStart;

        // context->playerIdleTime = elapsed.count();

        measurementStart = std::chrono::high_resolution_clock::now();
        for (auto& enemy : this->enemies) {
            if (enemy == nullptr)
                continue;
            enemy->idle();
        }
        elapsed = std::chrono::high_resolution_clock::now() - measurementStart;
        context->addEnemyIdleTimer(elapsed.count());
        // context->enemyIdleTime = elapsed.count();

        measurementStart = std::chrono::high_resolution_clock::now();
        for (auto& projectile : this->projectiles) {
            if (projectile == nullptr)
                continue;
            projectile->idle();
        }
        elapsed = std::chrono::high_resolution_clock::now() - measurementStart;
        // context->projectileIdleTime = elapsed.count();
    }
}

void Game::createPlayer(double x, double y, double size) {
    this->player =
        std::unique_ptr<Player>(new Player(x, y, 0, size, CHARACTER_3D));
    player->setShirtColor({0.0f, .5f, .0f});
    this->cam->setFollowTarget(this->player.get());
    this->playersColliders.push_back(this->player.get()->getCollider());
}

void Game::createEnemy(double x, double y, double size) {
    auto enemy = std::unique_ptr<Enemy>(new Enemy(x, y, 0, size));
    enemy->setShirtColor({1.0f, 0.0f, 0.0f});
    this->enemyColliders.push_back(enemy->getCollider());
    this->enemies.push_back(std::move(enemy));
}

Camera* Game::getMainCamera() { return this->cam.get(); }

Map* Game::getMap() { return this->map.get(); }

std::vector<Enemy*> Game::getEnemies() {
    std::vector<Enemy*> enemies;
    for (auto& enemy : this->enemies) {
        enemies.push_back(enemy.get());
    }
    return enemies;
}

void Game::createProjectile(float x, float y, float z, float size, float angle,
                            ProjectileType type, float speed) {
    auto proj = std::unique_ptr<Projectile>(
        new Projectile(x, y, z, size, angle, type, speed));
    this->projectilesColliders.push_back(proj->getCollider());
    this->projectiles.push_back(std::move(proj));
}

void Game::deleteProjectile(Projectile& projectile) {
    for (auto it = this->projectiles.begin(); it != this->projectiles.end();
         ++it) {
        auto curProjectile = (*it).get();
        if (curProjectile == &projectile) {
            this->projectiles.erase(it);
            break;
        }
    }
}

void Game::deleteEnemy(Enemy& enemy) {
    Collider* enemyCollider = enemy.getCollider();
    for (auto it = this->enemyColliders.begin();
         it != this->enemyColliders.end(); ++it) {
        Collider* curCollider = *it;
        if (enemyCollider == curCollider) {
            this->enemyColliders.erase(it);
            break;
        }
    }
    for (auto it = this->enemies.begin(); it != this->enemies.end(); ++it) {
        auto curEnemy = (*it).get();
        if (&enemy == curEnemy) {
            this->enemies.erase(it);
            break;
        }
    }
}

void Game::setState(GameState state) { this->state = state; }

void Game::togglePause() {
    if (this->state == GameState::PLAYING) {
        this->state = GameState::PAUSED;
    } else if (this->state == GameState::PAUSED) {
        this->state = GameState::PLAYING;
    }
}

bool Game::canRestart() {
    return this->state == GameState::OVER || this->state == GameState::WON;
}

void Game::drawGameOverScreen() {
    static const char* topText = "Game Over!";
    static const int topTextSize = strlen(topText);
    static int topTextWidth = 0;
#ifdef USE_GLUT
    for (long unsigned int i = 0; i < strlen(topText); i++) {
        topTextWidth += glutBitmapWidth(context->font, topText[i]);
    }

    static const char* bottomText = "Press R to restart";
    static const unsigned long int bottomTextSize = strlen(bottomText);
    static int bottomTextWidth = 0;
    for (long unsigned int i = 0; i < bottomTextSize; i++) {
        bottomTextWidth += glutBitmapWidth(context->font, bottomText[i]);
    }
#endif

    glPushMatrix();
    glColor4f(0.0f, 0.0f, 0.0f, 0.8f);
    glTranslatef(this->cam->getPosition().x, this->cam->getPosition().y, 0);
    glBegin(GL_QUADS);
    glVertex2f(-250.0f, -250.0f);
    glVertex2f(250.0f, -250.0f);
    glVertex2f(250.0f, 250.0f);
    glVertex2f(-250.0f, 250.0f);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);

    glPopMatrix();
    char* tmpString;
    glColor3f(1.0f, .0f, .0f);
    sprintf(context->textBuffer, "%s", topText);
    tmpString = context->textBuffer;
    glRasterPos2f(this->cam->getPosition().x - topTextSize / 2,
                  this->cam->getPosition().y);
#ifdef USE_GLUT
    while (*tmpString) {
        glutBitmapCharacter(context->font, *tmpString);
        tmpString++;
    }
    glColor3f(1.0f, 1.0f, 1.0f);

    glRasterPos2f(this->cam->getPosition().x - bottomTextSize / 2,
                  this->cam->getPosition().y + 4);
    sprintf(context->textBuffer, "%s", bottomText);
    tmpString = context->textBuffer;
    while (*tmpString) {
        glutBitmapCharacter(context->font, *tmpString);
        tmpString++;
    }
#endif
}

void Game::drawWinScreen() {
    static const char* topText = "You Won!";
    static const unsigned long int topTextSize = strlen(topText);
    static int topTextWidth = 0;
#ifdef USE_GLUT
    for (unsigned long int i = 0; i < strlen(topText); i++) {
        topTextWidth += glutBitmapWidth(context->font, topText[i]);
    }

    static const char* bottomText = "Press R to restart";
    static const int bottomTextSize = strlen(bottomText);
    static int bottomTextWidth = 0;
    for (int i = 0; i < bottomTextSize; i++) {
        bottomTextWidth += glutBitmapWidth(context->font, bottomText[i]);
    }
#endif
    glPushMatrix();
    glColor4f(0.0f, 0.0f, 0.0f, 0.8f);
    glTranslatef(this->cam->getPosition().x, this->cam->getPosition().y, 0);
    glBegin(GL_QUADS);
    glVertex2f(-250.0f, -250.0f);
    glVertex2f(250.0f, -250.0f);
    glVertex2f(250.0f, 250.0f);
    glVertex2f(-250.0f, 250.0f);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);

    glPopMatrix();
    char* tmpString;
    glColor3f(.0f, 1.0f, .0f);
    sprintf(context->textBuffer, "%s", topText);
    tmpString = context->textBuffer;
    glRasterPos2f(this->cam->getPosition().x - topTextSize / 2,
                  this->cam->getPosition().y);
#ifdef USE_GLUT
    while (*tmpString) {
        glutBitmapCharacter(context->font, *tmpString);
        tmpString++;
    }
    glColor3f(1.0f, 1.0f, 1.0f);

    glRasterPos2f(this->cam->getPosition().x - bottomTextSize / 2,
                  this->cam->getPosition().y + 4);
    sprintf(context->textBuffer, "%s", bottomText);
    tmpString = context->textBuffer;
    while (*tmpString) {
        glutBitmapCharacter(context->font, *tmpString);
        tmpString++;
    }
#endif
}

void Game::setupCamera() {
    if (this->renderMode == D2) {
        glm::fvec4 worldBounds = map->getWorldBounds();
        float deltaY = worldBounds[3] - worldBounds[2];
        this->cam->setDesiredSize({deltaY, deltaY});
        this->cam->setTargetYCoordinates(worldBounds[2] + deltaY / 2);
    } else {
        glm::fvec3 playerPosition = this->player->getPosition();
        this->cam->setCenter(this->player->getPosition());
        this->cam->setPosition(
            glm::fvec3(playerPosition.x, playerPosition.y, -100));
    }
}

const char* Game::getState() {
    if (this->state == GameState::PLAYING) {
        return "Playing";
    } else if (this->state == GameState::PAUSED) {
        return "Paused";
    } else if (this->state == GameState::OVER) {
        return "Over";
    } else if (this->state == GameState::WON) {
        return "Won";
    }
    return "";
}

void Game::toggleDimensions() {
    if (this->renderMode == RenderMode::D2) {
        this->renderMode = RenderMode::D3;
    } else {
        this->renderMode = RenderMode::D2;
    }
    this->player->toggleDimensionality();
}

void Game::postInit() {
    setupCamera();
    float platDepth = map->getWorldSize().y / 2;
    for (auto plat : map->getPlatforms()) {
        plat->setDepth(platDepth);
    }
    for (auto enemy : this->getEnemies()) {
        bool isGrounded = false;
        for (auto platform : this->map->getPlatforms()) {
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