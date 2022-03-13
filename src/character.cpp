#include "../include/character.h"
#include "../include/globalCtx.h"

#if defined(_WIN32) || defined(WIN32)
#define M_PI 3.14159265358979323846
#endif

extern GlobalCtx* context;

void Character::drawChest() {
    glPushMatrix();
    float chestXSize = this->size * 0.05f;
    float chestYSize = this->size * 0.2f;
    glColor3f(this->shirtColor.r, this->shirtColor.g, this->shirtColor.b);
    glTranslatef(0.0f, -0.05 * this->size, 0);
    if (this->drawMode == CharacterDrawMode::CHARACTER_2D) {
        glBegin(GL_QUADS);
        glVertex2f(-chestXSize, -chestYSize);
        glVertex2f(chestXSize, -chestYSize);
        glVertex2f(chestXSize, chestYSize);
        glVertex2f(-chestXSize, chestYSize);
        glEnd();
    } else {
        float offset = -chestXSize / 2;
        glm::fvec3 points[4] = {glm::fvec3(-chestXSize, -chestYSize, offset),
                                glm::fvec3(chestXSize, -chestYSize, offset),
                                glm::fvec3(chestXSize, chestYSize, offset),
                                glm::fvec3(-chestXSize, chestYSize, offset)};
        drawCubeFromExtrude(chestXSize, this->shirtColor, points);
    }

    glPopMatrix();
}

void Character::drawArm() {
    glPushMatrix();
    glTranslatef(0.0f, armPosition, 0.0f);
    glRotatef(this->armAngle, 0.0f, 0.0f, 1.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    if (this->drawMode == CharacterDrawMode::CHARACTER_2D) {
        glBegin(GL_QUADS);
        {
            glVertex2f(-this->armWidth, 0);
            glVertex2f(this->armWidth, 0);
            glVertex2f(this->armWidth, this->armHeight);
            glVertex2f(-this->armWidth, this->armHeight);
        }
        glEnd();
    } else {
        float offset = -this->armWidth / 2;
        glm::fvec3 points[4] = {
            glm::fvec3(-this->armWidth, 0, offset),
            glm::fvec3(this->armWidth, 0, offset),
            glm::fvec3(this->armWidth, this->armHeight, offset),
            glm::fvec3(-this->armWidth, this->armHeight, offset)};
        drawCubeFromExtrude(this->armWidth, glm::fvec3(1, 1, 1), points);
    }
    this->drawGun();
    glPopMatrix();
}

void Character::drawGun() {
    glPushMatrix();
    float gunSizeBig = 0.1 * this->size;
    float gunSizeSmall = gunSizeBig / 4;
    glColor3f(0.2f, .2f, .2f);
    glTranslatef(0.0f, this->armHeight, 0.0f);
    glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
    if (this->currentHeading == RIGHT) {
        glRotatef(180, 1.0f, 0, 0);
    }
    if (this->drawMode == CharacterDrawMode::CHARACTER_2D) {
        glBegin(GL_POLYGON);
        {
            glVertex2f(-gunSizeSmall, -gunSizeBig);
            glVertex2f(gunSizeSmall, -gunSizeBig);
            glVertex2f(gunSizeSmall, gunSizeSmall);
            glVertex2f(-gunSizeSmall, gunSizeSmall);

            glEnd();
        }
        glBegin(GL_POLYGON);
        {
            glVertex2f(-gunSizeSmall, 0);
            glVertex2f(2 * gunSizeBig, 0);
            glVertex2f(2 * gunSizeBig, 2 * gunSizeSmall);
            glVertex2f(-gunSizeSmall, 2 * gunSizeSmall);
        }
        glEnd();
    } else {
        float offset = -gunSizeSmall / 2;
        glm::fvec3 points[4] = {
            glm::fvec3(-gunSizeSmall, -gunSizeBig, offset),
            glm::fvec3(gunSizeSmall, -gunSizeBig, offset),
            glm::fvec3(gunSizeSmall, gunSizeSmall, offset),
            glm::fvec3(-gunSizeSmall, gunSizeSmall, offset)};
        drawCubeFromExtrude(gunSizeSmall, glm::fvec3(.2f, .2f, .2f), points);
        glm::fvec3 points2[4] = {
            glm::fvec3(-gunSizeSmall, 0, offset),
            glm::fvec3(2 * gunSizeBig, 0, offset),
            glm::fvec3(2 * gunSizeBig, 2 * gunSizeSmall, offset),
            glm::fvec3(-gunSizeSmall, 2 * gunSizeSmall, offset)};
        drawCubeFromExtrude(gunSizeSmall, glm::fvec3(.2f, .2f, .2f), points2);
    }

    glPopMatrix();
}

void Character::drawHead() {
    glTranslatef(0, -this->size * 0.3f, 0);
    if (context->getGameRef()->getCurrentRenderMode() == RenderMode::D2) {
        glBegin(GL_POLYGON);
        {
            for (int i = 0; i < 360; i += 10) {
                glVertex2f(this->size * 0.1f * cos(i * M_PI / 180),
                           this->size * 0.1f * sin(i * M_PI / 180));
            }
        }
        glEnd();

    } else {
        if (this->head) {
        }
        this->head->draw();
    }
}

void Character::drawLegs() {
    glPushMatrix();
    this->nextAnimFrame();
    float legSizeX = this->size * 0.05f;
    float legSizeY = this->size * 0.2f;
    glColor3f(0.1f, .1f, .2f);
    if (context->getGameRef()->getCurrentRenderMode() == RenderMode::D2) {
        glTranslatef(0, this->size * 0.4f, 0);
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
            glBegin(GL_POLYGON);
            {
                for (int i = 0; i < 360; i += 10) {
                    glVertex2f(0.05 * this->size * cos(i * M_PI / 180),
                               0.05 * this->size * sin(i * M_PI / 180));
                }
            }
            glEnd();
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
            glBegin(GL_POLYGON);
            {
                for (int i = 0; i < 360; i += 10) {
                    glVertex2f(0.05 * this->size * cos(i * M_PI / 180),
                               0.05 * this->size * sin(i * M_PI / 180));
                }
            }
            glEnd();
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
    } else {
        float offset = -legSizeX / 2;
        glTranslatef(0, this->size * 0.4f, 0);
        {
            glPushMatrix();
            glRotatef(-legRotation[0], 0, 0, 1);
            glm::fvec3 points[4] = {glm::fvec3(-legSizeX, 0, offset),
                                    glm::fvec3(legSizeX, 0, offset),
                                    glm::fvec3(legSizeX, legSizeY, offset),
                                    glm::fvec3(-legSizeX, legSizeY, offset)};
            drawCubeFromExtrude(legSizeX, glm::fvec3(.2f, .2f, .2f), points);
            glTranslatef(0, legSizeY, 0);
            // glBegin(GL_POLYGON);
            // {
            //     for (int i = 0; i < 360; i += 10) {
            //         glVertex2f(0.05 * this->size * cos(i * M_PI / 180),
            //                    0.05 * this->size * sin(i * M_PI / 180));
            //     }
            // }
            // glEnd();
            glRotatef(legRotation[1], 0, 0, 1);
            glm::fvec3 points2[4] = {glm::fvec3(-legSizeX, 0, offset),
                                     glm::fvec3(legSizeX, 0, offset),
                                     glm::fvec3(legSizeX, legSizeY, offset),
                                     glm::fvec3(-legSizeX, legSizeY, offset)};
            drawCubeFromExtrude(legSizeX, glm::fvec3(.2f, .2f, .2f), points2);
            glPopMatrix();
        }
        {
            glPushMatrix();
            glRotatef(legRotation[2], 0, 0, 1);
            glm::fvec3 points3[4] = {glm::fvec3(-legSizeX, 0, offset),
                                     glm::fvec3(legSizeX, 0, offset),
                                     glm::fvec3(legSizeX, legSizeY, offset),
                                     glm::fvec3(-legSizeX, legSizeY, offset)};
            drawCubeFromExtrude(legSizeX, glm::fvec3(.2f, .2f, .2f), points3);
            glTranslatef(0, legSizeY, 0);
            // glBegin(GL_POLYGON);
            // {
            //     for (int i = 0; i < 360; i += 10) {
            //         glVertex2f(0.05 * this->size * cos(i * M_PI / 180),
            //                    0.05 * this->size * sin(i * M_PI / 180));
            //     }
            // }
            // glEnd();
            glRotatef(legRotation[3], 0, 0, 1);
            glm::fvec3 points4[4] = {glm::fvec3(-legSizeX, 0, offset),
                                     glm::fvec3(legSizeX, 0, offset),
                                     glm::fvec3(legSizeX, legSizeY, offset),
                                     glm::fvec3(-legSizeX, legSizeY, offset)};
            drawCubeFromExtrude(legSizeX, glm::fvec3(.2f, .2f, .2f), points4);
            glPopMatrix();
        }
    }

    glPopMatrix();
}

void Character::nextAnimFrame() {
    const float deltaTimeBetweenFrames = .5f;
    if (context->getGameRef()->canRestart())
        return;
    glm::fvec4* targetAnims = nullptr;
    this->animTimer += context->getDeltaTime();
    curAnimCounter++;
    this->setLegsPosition(walkingFrames[0]);

    if (this->currentAnimState == AnimState::IDLE) {
        setLegsPosition(walkingFrames[0]);
        return;
    }

    if (this->currentAnimState == AnimState::JUMPING) {
        targetAnims = jumpingFrames;
    } else if (this->currentAnimState == AnimState::WALKING) {
        targetAnims = walkingFrames;
    }

    if (animTimer >= deltaTimeBetweenFrames) {
        animTimer = 0;
        currentAnimFrame++;
        if (currentAnimFrame > 1) {
            currentAnimFrame = 0;
        }
    }

    int nextFrame = currentAnimFrame == 1 ? 0 : 1;
    glm::fvec4 interpolated;
    for (int i = 0; i < 4; i++) {
        interpolated[i] = glm::mix(targetAnims[currentAnimFrame][i],
                                   targetAnims[nextFrame][i],
                                   animTimer / deltaTimeBetweenFrames);
    }
    setLegsPosition(interpolated);
    return;
};

void Character::setLegsPosition(glm::fvec4 position) {
    legRotation = position;
    for (int i = 0; i < 4; i++) {
        legRotation[i] = position[i];
        if (this->currentHeading == Heading::LEFT) {
            legRotation[i] *= -1;
        }
    }
}

void Character::handleResize() {
    armHeight = 0.5f * size;
    armPosition = 0.25f * size;
    armWidth = 0.05f * size;
}

void Character::toggleDimensionality() {
    if (context->getGameRef()->getCurrentRenderMode() == RenderMode::D2) {
        this->drawMode = CHARACTER_2D;
    } else {
        this->drawMode = CHARACTER_3D;
    }
}