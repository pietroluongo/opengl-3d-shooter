#ifndef PLAYER_H
#define PLAYER_H

#include "character.h"

class Player : public Character {
  private:
    void handleMovementKeys();

  public:
    Player(GLfloat x, GLfloat y, GLfloat size);
    virtual ~Player();
    void draw();
    void idle();
    void applyDamage(int damage) { Character::applyDamage(damage); };
};

#endif