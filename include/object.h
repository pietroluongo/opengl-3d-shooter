#ifndef OBJECT_H
#define OBJECT_H

#include "customTypes.h"
#include <GL/gl.h>

class Object {
  protected:
    glfvec2 position = {0, 0};
  public:
    Object();
    Object(GLfloat x, GLfloat y);
    virtual void draw() = 0;
    virtual void idle() = 0;
    glfvec2 getPosition();
    virtual void moveX(double amount);
    virtual void moveY(double amount);
    virtual void setPosition(glfvec2 position);
    virtual void setPosition(GLfloat x, GLfloat y);
    void drawAxis();
};

#endif