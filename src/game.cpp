#include "../include/game.h"

Game::Game() {
    this->player = new Player(0, 0, 100);
    this->platforms.push_back(new Platform(100.f, 0.f, 50.f, 50.f));
}

Game::~Game() {
    delete (this->player);
    for (auto platform : this->platforms) {
        delete (platform);
    }
}

glfvec2 Game::getPlayerPosition() { return this->player->getPosition(); }

void Game::draw() {
    this->player->draw();
    this->platforms[0]->draw();
}

Player* Game::getPlayer() { return this->player; }

void Game::idle() { this->player->idle(); }