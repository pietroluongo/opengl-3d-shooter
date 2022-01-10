#ifndef GAME_H
#define GAME_H

#include "../include/camera.h"
#include "../include/enemy.h"
#include "../include/map.h"
#include "../include/platform.h"
#include "../include/player.h"
#include "../include/projectile.h"

#include <vector>

class Game {
    Player* player = nullptr;
    Camera* cam = nullptr;
    Map* map = nullptr;
    std::vector<Enemy*> enemies;
    std::vector<Projectile*> projectiles;

  public:
    Game();
    ~Game();
    glfvec2 getPlayerPosition();
    void draw();
    Player* getPlayer();
    void idle();
    void createPlayer(double x, double y, double size);
    void createEnemy(double x, double y, double size);
    void createProjectile(double x, double y, double size);
    Camera* getMainCamera();
    Map* getMap();
    std::vector<Enemy*> getEnemies();
};

#endif