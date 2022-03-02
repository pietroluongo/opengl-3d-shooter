#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "character.h"
#include "collider.h"
#include "object.h"

enum ProjectileType { PROJECTILE_TYPE_PLAYER, PROJECTILE_TYPE_ENEMY };

class Projectile : public Object {

  private:
    float angle;
    ProjectileType type;
    float speed;

  public:
    Projectile(float x, float y, float z, float size, float angle,
               ProjectileType type, float speed);
    virtual ~Projectile();
    virtual void draw();
    virtual void idle();
    virtual void setPosition(glfvec2 position);
    virtual void setPosition(GLfloat x, GLfloat y);
    bool checkCollisions();
    virtual std::vector<std::vector<Collider*>*> colliders();
};

#endif