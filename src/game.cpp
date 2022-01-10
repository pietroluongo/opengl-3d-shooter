#include "../include/game.h"

Game::Game() {
    this->player = nullptr;
    this->map = new Map();
    this->cam = new Camera();
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
}

glfvec2 Game::getPlayerPosition() { return this->player->getPosition(); }

void Game::draw() {
    this->map->draw();
    this->player->draw();
    for (auto enemy : this->enemies) {
        enemy->draw();
    }
}

Player* Game::getPlayer() { return this->player; }

void Game::idle() {
    this->player->idle();
    this->cam->idle();
    for (auto enemy : this->enemies) {
        enemy->idle();
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