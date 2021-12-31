#ifndef CUSTOM_TYPES_H
#define CUSTOM_TYPES_H
#include "../libs/glm/glm.hpp"
#include <GL/gl.h>
#include <memory>

enum pivotPosition { TOP_LEFT, CENTER, BOT_LEFT };

using glivec2 = glm::vec<2, GLint, glm::defaultp>;
using glivec3 = glm::vec<3, GLint, glm::defaultp>;

using glfvec2 = glm::vec<2, GLfloat, glm::defaultp>;
using glfvec3 = glm::vec<3, GLfloat, glm::defaultp>;

#endif