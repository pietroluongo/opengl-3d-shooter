#ifndef PLAYER_H
#define PLAYER_H

#include "../include/platform.h"
#include "character.h"

class Player : public Character {
  private:
    void handleMovementKeys();
    double jumpTime = 0;

  public:
    bool isRequestingJump = false;
    bool wasRequestingJump = false;
    bool shouldIncreaseHeight = false;
    Player(GLfloat x, GLfloat y, GLfloat size);
    virtual ~Player();
    void draw();
    void idle();
    void applyDamage(int damage) { Character::applyDamage(damage); };
    void updateArmAngle();
    bool checkCollision(Platform* platform);
    void handleJump();
    void shoot();
    void updateAnimState();
    float* tmp_getSize() { return &this->size; };
    double getJumpTime() { return this->jumpTime; };
};

#endif