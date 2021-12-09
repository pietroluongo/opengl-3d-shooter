#ifndef GAME_H
#define GAME_H
#include "../include/platform.h"
#include "../include/player.h"
#include <vector>

class Game {
    Player* player;
    std::vector<Platform*> platforms;

  public:
    Game();
    glfvec2 getPlayerPosition();
    void draw();
    Player* getPlayer();
    void idle();
};

#endif