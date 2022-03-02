#include "../include/solidUtils.h"
#include <GL/gl.h>

void drawCubePure(glm::vec3 size, glm::vec3 color, PivotPoint pivot) {
    glPushMatrix();
    glColor3f(color.r, color.g, color.b);
    if (pivot == PIVOT_CENTER_BOTTOM) {

        glTranslatef(0, size.y, 0);
    }

    glBegin(GL_QUADS);

    glVertex3f(-size.x, -size.y, size.z);
    glVertex3f(size.x, -size.y, size.z);
    glVertex3f(size.x, size.y, size.z);
    glVertex3f(-size.x, size.y, size.z);

    // back
    glVertex3f(-size.x, -size.y, -size.z);
    glVertex3f(-size.x, size.y, -size.z);
    glVertex3f(size.x, size.y, -size.z);
    glVertex3f(size.x, -size.y, -size.z);

    // left
    glVertex3f(-size.x, -size.y, size.z);
    glVertex3f(-size.x, -size.y, -size.z);
    glVertex3f(-size.x, size.y, -size.z);
    glVertex3f(-size.x, size.y, size.z);

    // right
    glVertex3f(size.x, -size.y, size.z);
    glVertex3f(size.x, size.y, size.z);
    glVertex3f(size.x, size.y, -size.z);
    glVertex3f(size.x, -size.y, -size.z);

    // top
    glVertex3f(-size.x, size.y, size.z);
    glVertex3f(size.x, size.y, size.z);
    glVertex3f(size.x, size.y, -size.z);
    glVertex3f(-size.x, size.y, -size.z);

    // bottom
    glVertex3f(-size.x, -size.y, size.z);
    glVertex3f(size.x, -size.y, size.z);
    glVertex3f(size.x, -size.y, -size.z);
    glVertex3f(-size.x, -size.y, -size.z);

    glEnd();
    glPopMatrix();
}

void drawCube(glm::vec3 pos, glm::vec3 size, glm::vec3 color) {
    glPushMatrix();
    glTranslatef(pos.x, pos.y, pos.z);
    drawCubePure(size, color);
    glPopMatrix();
}