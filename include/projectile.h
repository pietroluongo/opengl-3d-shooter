#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "collider.h"
#include "object.h"

class Projectile : public Object {
  private:
    float size;
    Collider* collider;

  public:
    Projectile(float x, float y, float size);
    void draw();
    void idle();
    void moveX(double amount);
    void moveY(double amount);
    void setPosition(glfvec2 position);
    void setPosition(GLfloat x, GLfloat y);
    void drawAxis();
};

#endif