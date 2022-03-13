#include "../include/solidUtils.h"
#include <GL/gl.h>

#if defined(_WIN32) || defined(WIN32)
#define M_PI 3.14159265358979323846
#endif

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

    GLfloat materialEmission[] = {1.0, 1.0, 1.0, 1};
    GLfloat materialColorA[] = {0.2, 0.2, 0.2, 1};
    GLfloat materialColorD[] = {color.r, color.g, color.b, 1};
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1};
    GLfloat mat_shininess[] = {100.0};
    // glColor3f(color.r, color.g, color.b);

    glMaterialfv(GL_FRONT, GL_AMBIENT, materialColorA);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, materialColorD);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // X
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Y

    // front
    glBegin(GL_QUADS);
    glNormal3f(0, 0, -1);
    glVertex3f(points[0].x, points[0].y, points[0].z);
    glVertex3f(points[1].x, points[1].y, points[1].z);
    glVertex3f(points[2].x, points[2].y, points[2].z);
    glVertex3f(points[3].x, points[3].y, points[3].z);
    glEnd();

    // back
    glBegin(GL_QUADS);
    glNormal3f(0, 0, 1);
    glVertex3f(points[0].x, points[0].y, points[0].z + depth);
    glVertex3f(points[1].x, points[1].y, points[1].z + depth);
    glVertex3f(points[2].x, points[2].y, points[2].z + depth);
    glVertex3f(points[3].x, points[3].y, points[3].z + depth);
    glEnd();

    // left
    glBegin(GL_QUADS);
    glNormal3f(1, 0, 0);
    glVertex3f(points[0].x, points[0].y, points[0].z);
    glVertex3f(points[0].x, points[0].y, points[0].z + depth);
    glVertex3f(points[3].x, points[3].y, points[3].z + depth);
    glVertex3f(points[3].x, points[3].y, points[3].z);
    glEnd();

    // right
    glBegin(GL_QUADS);
    glNormal3f(-1, 0, 0);
    glVertex3f(points[1].x, points[1].y, points[1].z);
    glVertex3f(points[1].x, points[1].y, points[1].z + depth);
    glVertex3f(points[2].x, points[2].y, points[2].z + depth);
    glVertex3f(points[2].x, points[2].y, points[2].z);
    glEnd();

    // top
    glBegin(GL_QUADS);
    glNormal3f(0, 1, 0);
    glVertex3f(points[3].x, points[3].y, points[3].z);
    glVertex3f(points[2].x, points[2].y, points[2].z);
    glVertex3f(points[2].x, points[2].y, points[2].z + depth);
    glVertex3f(points[3].x, points[3].y, points[3].z + depth);
    glEnd();

    // bottom
    glBegin(GL_QUADS);
    glNormal3f(0, -1, 0);
    glVertex3f(points[0].x, points[0].y, points[0].z);
    glVertex3f(points[1].x, points[1].y, points[1].z);
    glVertex3f(points[1].x, points[1].y, points[1].z + depth);
    glVertex3f(points[0].x, points[0].y, points[0].z + depth);
    glEnd();
}

void buildSphere(double R, double space) {}

Sphere::Sphere(double R, double space) {
    int numVtx, radius;
    numVtx = (180 / space) * (2 + 360 / (2 * space)) * 4;
    this->vertices = std::unique_ptr<VertexData>(new VertexData[numVtx]);

    VertexData* vtx = this->vertices.get();
    radius = R;

    int n;
    double vR, lVR;
    double hR, lHR;
    double norm;
    n = 0;
    for (vR = 0; vR <= 180 - space; vR += space) {
        for (hR = 0; hR <= 360 + 2 * space; hR += 2 * space) {
            lVR = vR;
            lHR = hR;
            vtx[n].pos.x = R * sin(lHR / 180 * M_PI) * sin(lVR / 180 * M_PI);
            vtx[n].pos.y = R * cos(lHR / 180 * M_PI) * sin(lVR / 180 * M_PI);
            vtx[n].pos.z = R * cos(lVR / 180 * M_PI);
            vtx[n].txC.x = lVR / 180;
            vtx[n].txC.y = lHR / 360;
            norm =
                sqrt(vtx[n].pos.x * vtx[n].pos.x + vtx[n].pos.y * vtx[n].pos.y +
                     vtx[n].pos.z * vtx[n].pos.z);
            vtx[n].nrm.x = vtx[n].pos.x / norm;
            vtx[n].nrm.y = vtx[n].pos.y / norm;
            vtx[n].nrm.z = vtx[n].pos.z / norm;
            n++;

            lVR = vR + space;
            lHR = hR;
            vtx[n].pos.x = R * sin(lHR / 180 * M_PI) * sin(lVR / 180 * M_PI);
            vtx[n].pos.y = R * cos(lHR / 180 * M_PI) * sin(lVR / 180 * M_PI);
            vtx[n].pos.z = R * cos(lVR / 180 * M_PI);
            vtx[n].txC.y = lVR / 180;
            vtx[n].txC.y = lHR / 360;
            norm =
                sqrt(vtx[n].pos.x * vtx[n].pos.x + vtx[n].pos.y * vtx[n].pos.y +
                     vtx[n].pos.z * vtx[n].pos.z);
            vtx[n].nrm.x = vtx[n].pos.x / norm;
            vtx[n].nrm.y = vtx[n].pos.y / norm;
            vtx[n].nrm.z = vtx[n].pos.z / norm;
            n++;

            lVR = vR;
            lHR = hR + space;
            vtx[n].pos.x = R * sin(lHR / 180 * M_PI) * sin(lVR / 180 * M_PI);
            vtx[n].pos.y = R * cos(lHR / 180 * M_PI) * sin(lVR / 180 * M_PI);
            vtx[n].pos.z = R * cos(lVR / 180 * M_PI);
            vtx[n].txC.y = lVR / 180;
            vtx[n].txC.y = lHR / 360;
            norm =
                sqrt(vtx[n].pos.x * vtx[n].pos.x + vtx[n].pos.y * vtx[n].pos.y +
                     vtx[n].pos.z * vtx[n].pos.z);
            vtx[n].nrm.x = vtx[n].pos.x / norm;
            vtx[n].nrm.y = vtx[n].pos.y / norm;
            vtx[n].nrm.z = vtx[n].pos.z / norm;
            n++;

            lVR = vR + space;
            lHR = hR + space;
            vtx[n].pos.x = R * sin(lHR / 180 * M_PI) * sin(lVR / 180 * M_PI);
            vtx[n].pos.y = R * cos(lHR / 180 * M_PI) * sin(lVR / 180 * M_PI);
            vtx[n].pos.z = R * cos(lVR / 180 * M_PI);
            vtx[n].txC.y = lVR / 180;
            vtx[n].txC.y = lHR / 360;
            norm =
                sqrt(vtx[n].pos.x * vtx[n].pos.x + vtx[n].pos.y * vtx[n].pos.y +
                     vtx[n].pos.z * vtx[n].pos.z);
            vtx[n].nrm.x = vtx[n].pos.x / norm;
            vtx[n].nrm.y = vtx[n].pos.y / norm;
            vtx[n].nrm.z = vtx[n].pos.z / norm;
            n++;
        }
    }
    this->vertexCount = numVtx;
    this->radius = radius;
}

void Sphere::draw() {
    GLfloat materialColorD[] = {1.0, 1.0, 1.0, 1};
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1};
    GLfloat mat_shininess[] = {0.0};
    glColor3f(1, 1, 1);

    glMaterialfv(GL_FRONT, GL_DIFFUSE, materialColorD);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glBindTexture(GL_TEXTURE_2D, 0);
    auto error = glGetError();
    if (error != GL_NO_ERROR) {
        printf("err:%d\n", error);
    }
    VertexData* vtx = this->vertices.get();

    glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0; i < this->vertexCount; i++) {
        glNormal3f(vtx[i].nrm.x, vtx[i].nrm.y, vtx[i].nrm.z);
        glTexCoord2f(vtx[i].txC.x, vtx[i].txC.y);
        glVertex3f(vtx[i].pos.x, vtx[i].pos.y, vtx[i].pos.z);
    }
    glEnd();
}

Sphere::~Sphere() {}

void drawCoordinateSystem() {
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_QUADS);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(1.0, 0.0, 0.0);
    glVertex3f(1.0, 1.0, 0.0);
    glVertex3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glEnd();
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_QUADS);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 1.0, 0.0);
    glVertex3f(0.0, 1.0, 1.0);
    glVertex3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 0.0, 0.0);
    glEnd();
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_QUADS);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 1.0);
    glVertex3f(1.0, 0.0, 1.0);
    glVertex3f(1.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glEnd();
}