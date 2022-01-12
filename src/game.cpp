#include "../include/game.h"
#include <algorithm>

Game::Game() {
    this->player = nullptr;
    this->map = new Map();
    this->cam = new Camera();
}

Game::~Game() {
    printf("deleting game\n");
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
}

Player* Game::getPlayer() { return this->player; }

void Game::idle() {
    this->player->idle();
    this->cam->idle();
    for (auto enemy : this->enemies) {
        enemy->idle();
    }
    for (auto projectile : this->projectiles) {
        if (projectile != nullptr)
            projectile->idle();
    }
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

void Game::createProjectile(float x, float y, float size, float angle) {
    this->projectiles.push_back(new Projectile(x, y, size, angle));
}

void Game::deleteProjectile(Projectile* projectile) {
    printf("Deleting...\n");
    for (auto it = this->projectiles.begin(); it != this->projectiles.end();) {
        if (*it == projectile) {
            it = this->projectiles.erase(it);
        } else {
            it++;
        }
    }
}

void Game::deleteEnemy(Enemy* enemy) {
    auto it = std::find(this->enemies.begin(), this->enemies.end(), enemy);
    this->enemies.erase(it);
    delete (enemy);
}
