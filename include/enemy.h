#ifndef ENEMY_H
#define ENEMY_H
#include "character.h"
#include "object.h"

class Enemy : public Character {
  private:
    void handleMovement();
    void drawChest();
    void drawArm();

  public:
    Enemy(GLfloat x, GLfloat y, GLfloat size);
    virtual void draw();
    virtual void idle();
    virtual void updateArmAngle();
};

#endif