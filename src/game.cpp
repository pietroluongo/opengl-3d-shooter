#include "../include/game.h"

Game::Game() { this->player = new Player(); }

glfvec2 Game::getPlayerPosition() { return this->player->getPosition(); }

void Game::draw() { this->player->draw(); }

Player* Game::getPlayer() { return this->player; }