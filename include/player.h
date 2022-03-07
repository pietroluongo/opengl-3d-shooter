#ifndef PLAYER_H
#define PLAYER_H

#include "../include/platform.h"
#include "character.h"

enum MouseMode {
    MOUSE_MODE_DUAL_AXIS,
    MOUSE_MODE_SINGLE_AXIS,
};

class Player : public Character {
  private:
    void handleMovementKeys();
    double jumpTime = 0;

    bool isRequestingJump = false;
    bool wasRequestingJump = false;
    bool shouldIncreaseHeight = false;
    bool isRequestingMove = false;

    bool isRequestingFire = false;

    bool hasHitHead = false;

    MouseMode mouseMode;

  public:
    bool isInvincible = false;

    Player(GLfloat x, GLfloat y, GLfloat z, GLfloat size,
           CharacterDrawMode mode = CHARACTER_2D);
    virtual ~Player();
    void draw();
    void idle();
    void applyDamage(int damage) { Character::applyDamage(damage); };
    void updateArmAngle();
    bool checkCollision(Platform* platform);
    void handleJump();
    void shoot();
    void updateAnimState();
    double getJumpTime() { return this->jumpTime; };
    glm::fvec3 getEyePosition();
    glm::fvec3 getDollyPosition();
    virtual void kill();
    virtual std::vector<std::vector<Collider*>*> colliders();
};

#endif