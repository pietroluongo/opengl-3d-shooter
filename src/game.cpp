#include "../include/game.h"

Game::Game() { this->player = NULL; }

Game::~Game() {
    if (this->player != NULL)
        delete (this->player);
    for (auto platform : this->platforms) {
        delete (platform);
    }
}

glfvec2 Game::getPlayerPosition() { return this->player->getPosition(); }

void Game::draw() {
    this->player->draw();
    for (auto platform : this->platforms) {
        platform->draw();
    }
}

Player* Game::getPlayer() { return this->player; }

void Game::idle() { this->player->idle(); }

void Game::addPlatform(Platform* platform) {
    this->platforms.push_back(platform);
}

void Game::createPlayer(double x, double y, double size) {
    this->player = new Player(x, y, size);
}
