#include "../include/character.h"

// TODO: move this to class header!
glm::fvec4 frames[4] = {
    {20, 35, 10, 20}, {21, 35, 4, 15}, {-12, 35, -20, 15}, {-12, 35, -42, 15}};
int currentAnimFrame = 0;
int curAnimCounter = 0;

void Character::drawChest() {
    glPushMatrix();
    float chestXSize = this->size * 0.05f;
    float chestYSize = this->size * 0.2f;
    glTranslatef(0.0f, -0.4f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-chestXSize, -chestYSize);
    glVertex2f(chestXSize, -chestYSize);
    glVertex2f(chestXSize, chestYSize);
    glVertex2f(-chestXSize, chestYSize);
    glEnd();
    glPopMatrix();
}

void Character::drawArm() {
    glPushMatrix();
    glTranslatef(0.0f, this->armPosition, 0.0f);
    glRotatef(this->armAngle, 0.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);
    {
        glVertex2f(-this->armWidth, 0);
        glVertex2f(this->armWidth, 0);
        glVertex2f(this->armWidth, this->armHeight);
        glVertex2f(-this->armWidth, this->armHeight);
    }
    glEnd();
    glPopMatrix();
}

void Character::drawHead() {
    glTranslatef(0, -this->size * 0.4f, 0);
    glBegin(GL_POLYGON);
    {
        for (int i = 0; i < 360; i += 10) {
            glVertex2f(this->size * 0.1f * cos(i * M_PI / 180),
                       this->size * 0.1f * sin(i * M_PI / 180));
        }
    }
    glEnd();
}

void Character::drawLegs() {
    glPushMatrix();
    this->nextAnimFrame();
    float legSizeX = this->size * 0.05f;
    float legSizeY = this->size * 0.25f;
    glTranslatef(0, this->size * 0.5f, 0);
    {
        glPushMatrix();
        glRotatef(-legRotation[0], 0, 0, 1);
        glBegin(GL_POLYGON);
        {
            glVertex2f(-legSizeX, 0);
            glVertex2f(legSizeX, 0);
            glVertex2f(legSizeX, legSizeY);
            glVertex2f(-legSizeX, legSizeY);
        }
        glEnd();
        glTranslatef(0, legSizeY, 0);
        glRotatef(legRotation[1], 0, 0, 1);
        glBegin(GL_POLYGON);
        {
            glVertex2f(-legSizeX, 0);
            glVertex2f(legSizeX, 0);
            glVertex2f(legSizeX, legSizeY);
            glVertex2f(-legSizeX, legSizeY);
        }
        glEnd();
        glPopMatrix();
    }
    {
        glPushMatrix();
        glRotatef(legRotation[2], 0, 0, 1);
        glBegin(GL_POLYGON);
        {
            glVertex2f(-legSizeX, 0);
            glVertex2f(legSizeX, 0);
            glVertex2f(legSizeX, legSizeY);
            glVertex2f(-legSizeX, legSizeY);
        }
        glEnd();
        glTranslatef(0, legSizeY, 0);
        glRotatef(legRotation[3], 0, 0, 1);
        glBegin(GL_POLYGON);
        {
            glVertex2f(-legSizeX, 0);
            glVertex2f(legSizeX, 0);
            glVertex2f(legSizeX, legSizeY);
            glVertex2f(-legSizeX, legSizeY);
        }
        glEnd();
        glPopMatrix();
    }
    glPopMatrix();
}

int Character::nextAnimFrame() {
    curAnimCounter++;
    if (this->currentState == AnimState::IDLE) {
        for (int i = 0; i < 4; i++) {
            this->legRotation[i] = frames[0][i];
            if (this->currentHeading == Heading::LEFT) {
                this->legRotation[i] *= -1;
            }
        }
        return 0;
    }
    if (curAnimCounter < 100)
        return currentAnimFrame;
    curAnimCounter = 0;
    currentAnimFrame++;
    if (currentAnimFrame > 3) {
        currentAnimFrame = 0;
    }
    for (int i = 0; i < 4; i++) {
        this->legRotation[i] = frames[currentAnimFrame][i];
        if (this->currentHeading == Heading::LEFT) {
            this->legRotation[i] *= -1;
        }
    }
    return currentAnimFrame;
};