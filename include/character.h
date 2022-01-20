#ifndef CHARACTER_H
#define CHARACTER_H

#include "collider.h"
#include "object.h"

enum AnimState { IDLE, WALKING, JUMPING, DEAD };

class Character : public Object {
  protected:
    float armHeight = 0.4f * size;
    float armPosition = 0.5f * size;
    float armWidth = 0.05f * size;
    int health = 100;
    AnimState currentState = AnimState::IDLE;

    virtual void drawChest() = 0;
    virtual void drawArm() = 0;

  public:
    // Public for debug reasons
    float armAngle = 0.0f;

    Character(GLfloat x, GLfloat y, GLfloat size)
        : Object(x, y, size){

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
    const char* getCurrentAnimState() {
        switch (this->currentState) {
        case AnimState::IDLE:
            return "IDLE";
        case AnimState::WALKING:
            return "WALKING";
        case AnimState::JUMPING:
            return "JUMP";
        case AnimState::DEAD:
            return "DEAD";
        }
        return "ERROR";
    };
};

#endif