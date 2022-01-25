#ifndef GAME_H
#define GAME_H

#include "../include/camera.h"
#include "../include/enemy.h"
#include "../include/map.h"
#include "../include/platform.h"
#include "../include/player.h"
#include "../include/projectile.h"

#include <vector>

enum GameState { PLAYING, PAUSED, OVER };

class Game {
    Player* player = nullptr;
    Camera* cam = nullptr;
    Map* map = nullptr;
    std::vector<Enemy*> enemies = {};
    std::vector<Projectile*> projectiles = {};
    std::vector<Collider*> colliders = {};
    GameState state = PLAYING;

  public:
    Game();
    ~Game();
    glfvec2 getPlayerPosition();
    void draw();
    Player* getPlayer();
    void idle();
    void createPlayer(double x, double y, double size);
    void createEnemy(double x, double y, double size);
    void createProjectile(float x, float y, float size, float angle,
                          ProjectileType type);
    Camera* getMainCamera();
    Map* getMap();
    std::vector<Enemy*> getEnemies();
    void deleteProjectile(Projectile* projectile);
    void deleteEnemy(Enemy* enemy);
    std::vector<Collider*> getAllObjectColliders();
    void setState(GameState state);
    void togglePause();
    bool canRestart();
    void drawGameOverScreen();
};

#endif