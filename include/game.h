#ifndef GAME_H
#define GAME_H
#include "../include/player.h"

class Game {
    Player* player;

  public:
    Game();
    glfvec2 getPlayerPosition();
    void draw();
    Player* getPlayer();
};

#endif