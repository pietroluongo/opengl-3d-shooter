#ifndef OBJECT_H
#define OBJECT_H

#include "customTypes.h"
#include <GL/gl.h>
#include <vector>

class Collider;
class Object {
  private:
    glfvec3 position = {0, 0, 0};
    glfvec3 positionDelta = {0, 0, 0};
    glfvec3 rotation = {1, 0, 0};
    glm::bvec4 collisionDirections = {false, false, false, false};
    double currentTime = 0;
    bool isAffectedByGravity = true;

  protected:
    float size = 1.0f;
    std::unique_ptr<Collider> collider;
    bool isGrounded = false;
    double fallTimer = 0;

  public:
    Object();
    Object(GLfloat x, GLfloat y, GLfloat z, GLfloat size);
    virtual ~Object();
    Collider* getCollider();
    double getFallTimer() { return this->fallTimer; };
    glfvec3 getPosition();
    glm::bvec4 getCollisionArr() { return this->collisionDirections; };
    virtual std::vector<std::vector<Collider*>*> colliders() = 0;
    virtual void draw() = 0;
    virtual void idle();
    virtual void moveForward(float distance);
    virtual void moveX(double amount);
    virtual void moveY(double amount);
    virtual void moveZ(double amount);
    virtual void rotateX(double angle);
    virtual void rotateY(double angle);
    virtual void rotateZ(double angle);
    virtual void setPosition(GLfloat x = 0, GLfloat y = 0, GLfloat z = 0);
    virtual void setPosition(glfvec2 position);
    virtual void setPosition(glfvec3 position);
    void drawAxis();
    void setIsAffectedByGravity(bool isAffectedByGravity);
    void teleport(float x = 0, float y = 0, float z = 0);
    void teleportToGround();
    glfvec3 getRotation() { return this->rotation; };
};

#endif