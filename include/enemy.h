#ifndef ENEMY_H
#define ENEMY_H
#include "character.h"
#include "object.h"

class Enemy : public Character {
  private:
    void handleMovement();
    void drawChest();
    void drawArm();
    int moveDirection = 1;
    bool wasGrounded = false;

  public:
    Enemy(GLfloat x, GLfloat y, GLfloat size);
    virtual ~Enemy();
    virtual void draw();
    virtual void idle();
    virtual void updateArmAngle();
};

#endif