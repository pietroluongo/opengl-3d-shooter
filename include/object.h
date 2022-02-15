#ifndef OBJECT_H
#define OBJECT_H

#include "customTypes.h"
#include <GL/gl.h>
#include <vector>

class Collider;
class Object {
  private:
    glfvec2 position = {0, 0};
    glfvec2 positionDelta = {0, 0};
    glm::bvec4 collisionDirections = {false, false, false, false};
    double currentTime = 0;
    bool isAffectedByGravity = true;

  protected:
    float size = 1.0f;
    Collider* collider;
    bool isGrounded = false;
    double fallTimer = 0;

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
    void teleport(float x, float y);
    void teleportToGround();
    void setIsAffectedByGravity(bool isAffectedByGravity);
    double getFallTimer() { return this->fallTimer; };
    virtual std::vector<std::vector<Collider*>*> colliders() = 0;
};

#endif