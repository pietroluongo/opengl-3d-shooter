#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "character.h"
#include "collider.h"
#include "object.h"

enum ProjectileType { PROJECTILE_TYPE_PLAYER, PROJECTILE_TYPE_ENEMY };

class Projectile : private Object {

  private:
    float angle;
    std::vector<Character*> colliderCharacters;
    float speed;

  public:
    Projectile(float x, float y, float size, float angle, ProjectileType type,
               float speed);
    virtual ~Projectile();
    virtual void draw();
    virtual void idle();
    virtual void setPosition(glfvec2 position);
    virtual void setPosition(GLfloat x, GLfloat y);
    void checkCollisions();
    const char* debug();
};

#endif