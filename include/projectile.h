#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "collider.h"
#include "object.h"

class Projectile : private Object {

  private:
    float angle;

  public:
    Projectile(float x, float y, float size, float angle);
    virtual ~Projectile();
    virtual void draw();
    virtual void idle();
    virtual void setPosition(glfvec2 position);
    virtual void setPosition(GLfloat x, GLfloat y);
    void checkCollisions();
    const char* debug();
};

#endif