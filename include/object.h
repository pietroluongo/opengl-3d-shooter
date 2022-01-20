#ifndef OBJECT_H
#define OBJECT_H

#include "customTypes.h"
#include <GL/gl.h>

class Collider;
class Object {
  protected:
    glfvec2 position = {0, 0};
    float size = 1.0f;
    Collider* collider;
    bool isGrounded = false;
    glm::bvec4 collisionDirections = {false, false, false, false};

  public:
    Object();
    Object(GLfloat x, GLfloat y, GLfloat size);
    virtual ~Object();
    virtual void draw() = 0;
    virtual void idle();
    glfvec2 getPosition();
    virtual void moveX(double amount);
    virtual void moveY(double amount);
    virtual void setPosition(glfvec2 position);
    virtual void setPosition(GLfloat x, GLfloat y);
    void drawAxis();
    Collider* getCollider();
    glm::bvec4 getCollisionArr() { return this->collisionDirections; };
};

#endif