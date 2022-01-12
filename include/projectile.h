#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "collider.h"
#include "object.h"

class Projectile : private Object {

  private:
    float size;
    float angle;
    Collider* collider;

  public:
    Projectile(float x, float y, float size, float angle);
    virtual ~Projectile();
    virtual void draw();
    virtual void idle();
    virtual void moveX(double amount);
    virtual void moveY(double amount);
    virtual void setPosition(glfvec2 position);
    virtual void setPosition(GLfloat x, GLfloat y);
    virtual void accelerateX(double amount);
    virtual void accelerateY(double amount);
    void checkCollisions();
    const char* debug();
};

#endif