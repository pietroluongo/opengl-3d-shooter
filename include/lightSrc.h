#ifndef LIGHT_SRC_H
#define LIGHT_SRC_H

#include "../libs/glm/glm.hpp"

class LightSource {
    glm::fvec3 position;
    float intensity;
    bool enabled;
    int lightId;

  public:
    LightSource(int id);
    void draw();
    void setPosition(glm::fvec3 pos);
    void enable() { this->enabled = true; }
    void disable() { this->enabled = false; }
    glm::fvec3 getPosition() { return this->position; }
    int getId() { return this->lightId; }
    float getIntensity() { return this->intensity; }
    void setIntensity(float intensity) { this->intensity = intensity; }
};

#endif