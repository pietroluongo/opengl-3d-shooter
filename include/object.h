#ifndef OBJECT_H
#define OBJECT_H

#include "customTypes.h"
#include <GL/gl.h>

class Object {
  protected:
    glfvec2 position = {0, 0};
    glfvec2 speed = {0, 0};
    glfvec2 maxSpeed = {75, 100};
    glfvec2 speedFalloff = {50, 50};

  public:
    Object();
    Object(GLfloat x, GLfloat y);
    virtual ~Object();
    virtual void draw() = 0;
    virtual void idle();
    glfvec2 getPosition();
    virtual void moveX(double amount);
    virtual void moveY(double amount);
    virtual void setPosition(glfvec2 position);
    virtual void setPosition(GLfloat x, GLfloat y);
    virtual void accelerateX(double amount);
    virtual void accelerateY(double amount);
    void drawAxis();
    glfvec2 getCurrentSpeed();
};

#endif