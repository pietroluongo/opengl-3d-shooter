#ifndef PLAYER_H
#define PLAYER_H

#include "../include/platform.h"
#include "character.h"

class Player : public Character {
  private:
    void handleMovementKeys();
    void drawChest();
    void drawArm();
    bool isJumping = false;
    glm::bvec4 collisionDirections = {false, false, false, false};

  public:
    Player(GLfloat x, GLfloat y, GLfloat size);
    virtual ~Player();
    void draw();
    void idle();
    void applyDamage(int damage) { Character::applyDamage(damage); };
    void updateArmAngle();
    bool checkCollision(Platform* platform);
    void jump();
    void shoot();
    void updateAnimState();
    glm::bvec4 getCollisionArr() { return this->collisionDirections; };
};

#endif