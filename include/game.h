#ifndef GAME_H
#define GAME_H

#include "../include/camera.h"
#include "../include/enemy.h"
#include "../include/map.h"
#include "../include/platform.h"
#include "../include/player.h"
#include "../include/projectile.h"

#include <vector>

enum GameState { PLAYING, PAUSED, OVER, WON };

enum RenderMode { D2, D3 };

class Game {
    std::unique_ptr<Player> player = nullptr;
    std::unique_ptr<Camera> cam = nullptr;
    std::unique_ptr<Map> map = nullptr;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::vector<Collider*> enemyColliders;
    std::vector<Collider*> playersColliders;

    std::vector<std::unique_ptr<Projectile>> projectiles;
    std::vector<Collider*> projectilesColliders;

    std::vector<Collider*> colliders;

    GameState state = PLAYING;

    RenderMode renderMode = D3;

  public:
    Game();
    ~Game();
    glfvec3 getPlayerPosition();
    void draw();
    Player* getPlayer();
    void idle();
    void createPlayer(double x, double y, double size);
    void createEnemy(double x, double y, double size);
    void createProjectile(float x, float y, float size, float angle,
                          ProjectileType type, float speed);
    Camera* getMainCamera();
    Map* getMap();
    std::vector<Enemy*> getEnemies();
    void deleteProjectile(Projectile& projectile);
    void deleteEnemy(Enemy& enemy);
    void setState(GameState state);
    void togglePause();
    bool canRestart();
    void drawGameOverScreen();
    void drawWinScreen();
    void setupCamera();
    const char* getState();
    std::vector<Collider*>* getEnemyColliders() {
        return &this->enemyColliders;
    }
    std::vector<Collider*>* getProjectilesColliders() {
        return &this->projectilesColliders;
    }
    std::vector<Collider*>* getPlayerColliders() {
        return &this->playersColliders;
    }
    unsigned long getProjectileCount() { return projectiles.size(); }
    void toggleDimensions();
    RenderMode getCurrentRenderMode() { return this->renderMode; }
};

#endif