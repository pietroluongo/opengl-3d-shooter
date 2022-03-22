#include "../include/lightSrc.h"
#include "../libs/glm/gtc/type_ptr.hpp"
#include <GL/gl.h>

LightSource::LightSource(int id) {
    position = glm::fvec3(0.0f, 0.0f, 0.0f);
    intensity = 1.0f;
    enabled = false;
    lightId = id;
}

void LightSource::draw() {
    glPushMatrix();
    glLoadIdentity();
    float fourth;
    if (this->type == LIGHT_DIRECTIONAL) {
        fourth = 0.0f;
    } else {
        fourth = 1.0f;
    }
    glm::fvec4 lightPos = glm::fvec4(this->position, fourth);
    glLightfv(GL_LIGHT0 + this->lightId, GL_POSITION, glm::value_ptr(lightPos));
    glLightfv(GL_LIGHT0 + this->lightId, GL_DIFFUSE,
              glm::value_ptr(glm::fvec3(1.0f, 1.0f, 1.0f)));

    if (this->type == LIGHT_SPOT) {
        glLightf(GL_LIGHT0 + this->lightId, GL_SPOT_CUTOFF, 45.0);
        glLightfv(GL_LIGHT0 + this->lightId, GL_SPOT_DIRECTION,
                  glm::value_ptr(this->direction));
    } else {
        glLightf(GL_LIGHT0 + this->lightId, GL_SPOT_CUTOFF, 180.0);
        glLightfv(GL_LIGHT0 + this->lightId, GL_SPOT_DIRECTION,
                  glm::value_ptr(this->direction));
    }

    glPopMatrix();
}

void LightSource::setPosition(glm::fvec3 pos) { this->position = pos; }

void LightSource::toggle() { this->enabled ? this->disable() : this->enable(); }

const char* LightSource::getMode() {
    if (this->type == LIGHT_DIRECTIONAL) {
        return "directional light";
    } else if (this->type == LIGHT_POINT) {
        return "point light";
    } else if (this->type == LIGHT_SPOT) {
        return "spot light";
    }
    return "unknown";
}