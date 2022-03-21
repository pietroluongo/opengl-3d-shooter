#ifndef LIGHT_SRC_H
#define LIGHT_SRC_H

#include "../libs/glm/glm.hpp"
#include <GL/gl.h>
#include <cstdio>

class LightSource {
    glm::fvec3 position = {};
    float intensity;
    bool enabled;
    int lightId;

  public:
    LightSource(int id);
    void draw();
    void setPosition(glm::fvec3 pos);
    void enable() {
        this->enabled = true;
        printf("enabling light %d\n", this->lightId);
        glEnable(GL_LIGHT0 + this->lightId);
    }
    void disable() {
        this->enabled = false;
        printf("disabling light %d\n", this->lightId);
        glDisable(GL_LIGHT0 + this->lightId);
    }
    glm::fvec3 getPosition() { return this->position; }
    int getId() { return this->lightId; }
    float getIntensity() { return this->intensity; }
    void setIntensity(float intensity) { this->intensity = intensity; }
    void toggle();
    bool isEnabled() { return this->enabled; }
};

#endif