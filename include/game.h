#ifndef GAME_H
#define GAME_H
#include "../include/camera.h"
#include "../include/platform.h"
#include "../include/player.h"
#include <vector>

class Game {
    Player* player;
    Camera* cam;
    std::vector<Platform*> platforms;

  public:
    Game();
    ~Game();
    glfvec2 getPlayerPosition();
    void draw();
    Player* getPlayer();
    void idle();
    void addPlatform(Platform* platform);
    void createPlayer(double x, double y, double size);
    Camera* getMainCamera();
};

#endif