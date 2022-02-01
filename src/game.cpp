#include "../include/game.h"
#include "../include/globalCtx.h"
#include <algorithm>
#include <cstring>

extern GlobalCtx* context;

Game::Game() {
    this->player = nullptr;
    this->map = new Map();
    this->cam = new Camera();
    this->cam->setFollowMode(CAMERA_FOLLOW_MODE_SINGLE_AXIS);
}

Game::~Game() {
    if (this->player != nullptr)
        delete (this->player);
    if (this->cam != nullptr)
        delete (this->cam);
    if (this->map != nullptr)
        delete (this->map);
    for (auto enemy : this->enemies) {
        delete (enemy);
    }
    for (auto projectile : this->projectiles) {
        if (projectile != nullptr)
            delete (projectile);
    }
}

glfvec2 Game::getPlayerPosition() { return this->player->getPosition(); }

void Game::draw() {
    this->map->draw();
    this->player->draw();
    for (auto enemy : this->enemies) {
        enemy->draw();
    }
    for (auto projectile : this->projectiles) {
        if (projectile)
            projectile->draw();
    }
    if (this->state == GameState::OVER) {
        this->drawGameOverScreen();
    } else if (this->state == GameState::WON) {
        this->drawWinScreen();
    }
}

Player* Game::getPlayer() { return this->player; }

void Game::idle() {
    if (this->state == GameState::PLAYING) {
        this->player->idle();
        for (auto enemy : this->enemies) {
            enemy->idle();
        }
        for (auto projectile : this->projectiles) {
            if (projectile != nullptr)
                projectile->idle();
        }
    }
    this->cam->idle();
}

void Game::createPlayer(double x, double y, double size) {
    this->player = new Player(x, y, size);
    this->cam->setFollowTarget(this->player);
}

void Game::createEnemy(double x, double y, double size) {
    this->enemies.push_back(new Enemy(x, y, size));
}

Camera* Game::getMainCamera() { return this->cam; }

Map* Game::getMap() { return this->map; }

std::vector<Enemy*> Game::getEnemies() { return this->enemies; }

void Game::createProjectile(float x, float y, float size, float angle,
                            ProjectileType type, float speed) {
    this->projectiles.push_back(new Projectile(x, y, size, angle, type, speed));
}

void Game::deleteProjectile(Projectile* projectile) {
    auto it = std::find(this->projectiles.begin(), this->projectiles.end(),
                        projectile);
    if (it != this->projectiles.end()) {
        this->projectiles.erase(it);
    }
}

void Game::deleteEnemy(Enemy* enemy) {
    auto it = std::find(this->enemies.begin(), this->enemies.end(), enemy);
    if (it != this->enemies.end()) {
        this->enemies.erase(it);
    }
}

std::vector<Collider*> Game::getAllObjectColliders() {
    std::vector<Collider*> colliders;

    for (auto enemy : this->getEnemies()) {
        colliders.push_back(enemy->getCollider());
    }

    for (auto platform : this->getMap()->getPlatforms()) {
        colliders.push_back(platform->getCollider());
    }

    return colliders;
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
    for (int i = 0; i < strlen(topText); i++) {
        topTextWidth += glutBitmapWidth(context->font, topText[i]);
    }

    static const char* bottomText = "Press R to restart";
    static const int bottomTextSize = strlen(bottomText);
    static int bottomTextWidth = 0;
    for (int i = 0; i < bottomTextSize; i++) {
        bottomTextWidth += glutBitmapWidth(context->font, bottomText[i]);
    }

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
}

void Game::drawWinScreen() {
    static const char* topText = "You Won!";
    static const int topTextSize = strlen(topText);
    static int topTextWidth = 0;
    for (int i = 0; i < strlen(topText); i++) {
        topTextWidth += glutBitmapWidth(context->font, topText[i]);
    }

    static const char* bottomText = "Press R to restart";
    static const int bottomTextSize = strlen(bottomText);
    static int bottomTextWidth = 0;
    for (int i = 0; i < bottomTextSize; i++) {
        bottomTextWidth += glutBitmapWidth(context->font, bottomText[i]);
    }
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