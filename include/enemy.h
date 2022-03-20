#ifndef ENEMY_H
#define ENEMY_H
#include "character.h"
#include "object.h"

class Enemy : public Character {
  private:
    void handleMovement();
    int moveDirection = 1;
    bool wasGrounded = false;
    double enemyShootTimer = 0;
    double enemyTurnTimer = 0;
    int targetShootTimer = 0;
    int targetTurnTimer = 0;

  public:
    Enemy(GLfloat x, GLfloat y, GLfloat z, GLfloat size);
    virtual ~Enemy();
    virtual void draw();
    virtual void idle();
    virtual void updateArmAngle();
    virtual void shoot();
    virtual void kill();
    virtual std::vector<std::vector<Collider*>*> colliders();
};

#endif