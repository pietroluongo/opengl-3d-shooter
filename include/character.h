#ifndef CHARACTER_H
#define CHARACTER_H

#include "object.h"

class Character : public Object {
  protected:
    float size = 1.0f;
    int health = 100;

  public:
    Character(GLfloat x, GLfloat y) : Object(x, y){};
    virtual void draw() = 0;
    virtual void idle() = 0;
    virtual void applyDamage(int damage) { health -= damage; }
    void setSize(float size) { this->size = size; }
};

#endif