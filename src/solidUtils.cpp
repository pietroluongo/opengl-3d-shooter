#include "../include/solidUtils.h"
#include <GL/gl.h>

#if defined(_WIN32) || defined(WIN32)
#define M_PI 3.14159265358979323846
#endif

void drawCubeFromExtrude(float depth, glm::vec3 color, glm::vec3 points[4],
                         CubeTextureData textures) {

    GLfloat materialEmission[] = {.0, .0, .0, 1};
    GLfloat materialColorA[] = {0.2, 0.2, 0.2, 1};
    // GLfloat materialColorD[] = {color.r, color.g, color.b, 1};
    GLfloat materialColorD[] = {1.0f, 1.0f, 1.0f, 1};
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1};
    GLfloat mat_shininess[] = {100.0};
    glColor3f(1, 1, 1);

    glMaterialfv(GL_FRONT, GL_EMISSION, materialEmission);
    glMaterialfv(GL_FRONT, GL_AMBIENT, materialColorA);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, materialColorD);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // X
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Y

    double textureS = 0.2; // Bigger than 1, repeat

    // front - ok
    glBindTexture(GL_TEXTURE_2D, textures.front);
    glBegin(GL_QUADS);
    {
        glNormal3f(0, 0, -1);
        glTexCoord2f(points[0].x * textureS, points[0].y * textureS);
        glVertex3f(points[0].x, points[0].y, points[0].z);
        glTexCoord2f(points[1].x * textureS, points[1].y * textureS);
        glVertex3f(points[1].x, points[1].y, points[1].z);
        glTexCoord2f(points[2].x * textureS, points[2].y * textureS);
        glVertex3f(points[2].x, points[2].y, points[2].z);
        glTexCoord2f(points[3].x * textureS, points[3].y * textureS);
        glVertex3f(points[3].x, points[3].y, points[3].z);
    }

    glEnd();

    // back - ok
    glBindTexture(GL_TEXTURE_2D, textures.back);
    glBegin(GL_QUADS);
    {
        glNormal3f(0, 0, 1);
        glTexCoord2f(points[0].x * textureS, points[0].y * textureS);
        glVertex3f(points[0].x, points[0].y, points[0].z + depth);
        glTexCoord2f(points[1].x * textureS, points[1].y * textureS);
        glVertex3f(points[1].x, points[1].y, points[1].z + depth);
        glTexCoord2f(points[2].x * textureS, points[2].y * textureS);
        glVertex3f(points[2].x, points[2].y, points[2].z + depth);
        glTexCoord2f(points[3].x * textureS, points[3].y * textureS);
        glVertex3f(points[3].x, points[3].y, points[3].z + depth);
    }

    glEnd();

    // left ! top
    glBindTexture(GL_TEXTURE_2D, textures.top);
    glBegin(GL_QUADS);
    {
        float textureS = 0.2;
        glNormal3f(1, 0, 0);
        glTexCoord2f(points[0].x * textureS, points[0].z * textureS);
        glVertex3f(points[0].x, points[0].y, points[0].z);

        glTexCoord2f(points[0].x * textureS, points[0].z + depth * textureS);
        glVertex3f(points[0].x, points[0].y, points[0].z + depth);

        glTexCoord2f(points[3].x * textureS, points[3].z + depth * textureS);
        glVertex3f(points[3].x, points[3].y, points[3].z + depth);

        glTexCoord2f(points[3].x * textureS, points[3].z * textureS);
        glVertex3f(points[3].x, points[3].y, points[3].z);
    }
    glEnd();

    // right ! bottom
    glBindTexture(GL_TEXTURE_2D, textures.bottom);
    glBegin(GL_QUADS);
    {
        glNormal3f(-1, 0, 0);
        glTexCoord2f(points[1].x * textureS, points[1].z * textureS);
        glVertex3f(points[1].x, points[1].y, points[1].z);
        glTexCoord2f(points[1].x * textureS, (points[1].z + depth) * textureS);
        glVertex3f(points[1].x, points[1].y, points[1].z + depth);
        glTexCoord2f(points[2].x * textureS, (points[2].z + depth) * textureS);
        glVertex3f(points[2].x, points[2].y, points[2].z + depth);
        glTexCoord2f(points[2].x * textureS, points[2].z * textureS);
        glVertex3f(points[2].x, points[2].y, points[2].z);
        glEnd();
    }

    // top ! right
    glBindTexture(GL_TEXTURE_2D, textures.right);
    glBegin(GL_QUADS);
    {
        float textureS = 0.2;
        glNormal3f(0, 1, 0);

        glTexCoord2f(points[3].z * textureS, points[3].y * textureS);
        glVertex3f(points[3].x, points[3].y, points[3].z);

        glTexCoord2f(points[2].z * textureS, points[2].y * textureS);
        glVertex3f(points[2].x, points[2].y, points[2].z);

        glTexCoord2f((points[2].z + depth) * textureS, points[2].y * textureS);
        glVertex3f(points[2].x, points[2].y, (points[2].z + depth));

        glTexCoord2f((points[3].z + depth) * textureS, points[3].y * textureS);
        glVertex3f(points[3].x, points[3].y, points[3].z + depth);
    }

    glEnd();

    // bottom ! left
    glBindTexture(GL_TEXTURE_2D, textures.left);
    glBegin(GL_QUADS);
    {
        glNormal3f(0, -1, 0);
        glTexCoord2f(points[0].z * textureS, points[0].y * textureS);
        glVertex3f(points[0].x, points[0].y, points[0].z);
        glTexCoord2f(points[1].z * textureS, points[1].y * textureS);
        glVertex3f(points[1].x, points[1].y, points[1].z);
        glTexCoord2f((points[1].z + depth) * textureS, points[1].y * textureS);
        glVertex3f(points[1].x, points[1].y, points[1].z + depth);
        glTexCoord2f((points[0].z + depth) * textureS, points[0].y * textureS);
        glVertex3f(points[0].x, points[0].y, points[0].z + depth);
    }

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
            vtx[n].txC.y = lVR / 180;
            vtx[n].txC.x = lHR / 360;
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
            vtx[n].txC.x = lHR / 360;
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
            vtx[n].txC.x = lHR / 360;
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
            vtx[n].txC.x = lHR / 360;
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
    GLfloat materialEmission[] = {0.10, 0.10, 0.10, 1};
    GLfloat materialColorA[] = {0.2, 0.2, 0.2, 1};
    GLfloat materialColorD[] = {1.0, 1.0, 1.0, 1};
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1};
    GLfloat mat_shininess[] = {100.0};
    glColor3f(1, 1, 1);

    glMaterialfv(GL_FRONT, GL_EMISSION, materialEmission);
    glMaterialfv(GL_FRONT, GL_AMBIENT, materialColorA);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, materialColorD);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glBindTexture(GL_TEXTURE_2D, this->tex);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP); // X
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP); // Y

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