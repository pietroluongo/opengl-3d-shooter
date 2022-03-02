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

void drawCubeFromExtrude(float depth, glm::vec3 color, glm::vec3 points[4]) {
    glColor3f(color.r, color.g, color.b);

    glBegin(GL_QUADS);

    // front
    glVertex3f(points[0].x, points[0].y, points[0].z);
    glVertex3f(points[1].x, points[1].y, points[1].z);
    glVertex3f(points[2].x, points[2].y, points[2].z);
    glVertex3f(points[3].x, points[3].y, points[3].z);

    // back
    glVertex3f(points[0].x, points[0].y, points[0].z + depth);
    glVertex3f(points[1].x, points[1].y, points[1].z + depth);
    glVertex3f(points[2].x, points[2].y, points[2].z + depth);
    glVertex3f(points[3].x, points[3].y, points[3].z + depth);

    // left
    glVertex3f(points[0].x, points[0].y, points[0].z);
    glVertex3f(points[0].x, points[0].y, points[0].z + depth);
    glVertex3f(points[1].x, points[1].y, points[1].z + depth);
    glVertex3f(points[1].x, points[1].y, points[1].z);

    // right
    glVertex3f(points[2].x, points[2].y, points[2].z);
    glVertex3f(points[2].x, points[2].y, points[2].z + depth);
    glVertex3f(points[3].x, points[3].y, points[3].z + depth);
    glVertex3f(points[3].x, points[3].y, points[3].z);

    // top
    glVertex3f(points[0].x, points[0].y, points[0].z);
    glVertex3f(points[3].x, points[3].y, points[3].z);
    glVertex3f(points[3].x, points[3].y, points[3].z + depth);
    glVertex3f(points[0].x, points[0].y, points[0].z + depth);

    // bottom
    glVertex3f(points[0].x, points[0].y, points[0].z + depth);
    glVertex3f(points[1].x, points[1].y, points[1].z + depth);
    glVertex3f(points[2].x, points[2].y, points[2].z + depth);
    glVertex3f(points[3].x, points[3].y, points[3].z + depth);

    glEnd();
}