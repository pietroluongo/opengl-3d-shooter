#ifndef CHARACTER_H
#define CHARACTER_H

#include "collider.h"
#include "object.h"

class Character : public Object {
  protected:
    float size = 1.0f;
    float armHeight = 0.5f * size;
    float armWidth = 0.2f * size;
    int health = 100;

    virtual void drawChest() = 0;
    virtual void drawArm() = 0;

    bool canMoveX = true, canMoveY = true;
    Collider* collider;

  public:
    float armAngle = 0.0f;

    Character(GLfloat x, GLfloat y, GLfloat size) : Object(x, y) {
        this->setSize(size);
        this->collider =
            new Collider(x, y, size, size, this, pivotPosition::CENTER);
    };
    virtual void draw() = 0;
    virtual void idle() = 0;
    virtual void applyDamage(int damage) { health -= damage; }
    virtual void updateArmAngle() = 0;
    void setSize(float size) {
        this->size = size;
        this->armWidth = 0.1f * size;
        this->armHeight = 0.5f * size;
    }
    Collider* getCollider() { return this->collider; }
};

#endif