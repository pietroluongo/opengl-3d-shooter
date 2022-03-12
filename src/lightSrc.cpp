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
    glm::fvec4 lightPos = glm::fvec4(this->position, 1.0f);
    glLightfv(GL_LIGHT0 + this->lightId, GL_POSITION, glm::value_ptr(lightPos));
    glLightfv(GL_LIGHT0 + this->lightId, GL_DIFFUSE,
              glm::value_ptr(glm::fvec3(this->intensity, this->intensity,
                                        this->intensity)));
    glPopMatrix();
}

void LightSource::setPosition(glm::fvec3 pos) { this->position = pos; }
