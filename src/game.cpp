#include "../include/game.h"
#include "../include/globalCtx.h"
#include <algorithm>
#include <chrono>
#include <cstring>
#include <memory>

extern GlobalCtx* context;

Game::Game() {
    this->player = nullptr;
    this->map = std::unique_ptr<Map>(new Map());
    this->cam = std::unique_ptr<Camera>(new Camera());
    this->cam->setFollowMode(CAMERA_FOLLOW_MODE_SINGLE_AXIS);
}

Game::~Game() {}

glfvec2 Game::getPlayerPosition() { return this->player->getPosition(); }

void Game::draw() {
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
    this->cam->idle();
}

void Game::createPlayer(double x, double y, double size) {
    this->player = std::unique_ptr<Player>(new Player(x, y, size));
    player->setShirtColor({0.0f, .5f, .0f});
    this->cam->setFollowTarget(this->player.get());
}

void Game::createEnemy(double x, double y, double size) {
    auto enemy = std::unique_ptr<Enemy>(new Enemy(x, y, size));
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

void Game::createProjectile(float x, float y, float size, float angle,
                            ProjectileType type, float speed) {
    auto proj = std::unique_ptr<Projectile>(
        new Projectile(x, y, size, angle, type, speed));
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
    glm::fvec4 worldBounds = map->getWorldBounds();
    float deltaY = worldBounds[3] - worldBounds[2];
    this->cam->setDesiredSize({deltaY, deltaY});
    this->cam->setTargetYCoordinates(worldBounds[2] + deltaY / 2);
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