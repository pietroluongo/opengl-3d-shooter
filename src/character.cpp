#include "../include/character.h"
#include "../include/globalCtx.h"

extern GlobalCtx* context;

// glm::fvec4 frames[4] = {
// {25, 20, 10, 30}, {10, 25, 4, 15}, {-10, 10, -20, 30}, {-10, 5, -25, 20}};
glm::fvec4 frames[2] = {{25, 20, 10, 30}, {-10, 5, -25, 20}};

glm::fvec4 legRotation = {25, 20, 10, 30};

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

void Character::nextAnimFrame() {
    const float deltaTimeBetweenFrames = .5f;
    this->animTimer += context->getDeltaTime();
    curAnimCounter++;
    this->setLegsPosition(frames[0]);

    if (this->currentAnimState == AnimState::IDLE) {
        setLegsPosition(frames[0]);
        return;
    }

    // if (curAnimCounter < 250)
    //     return currentAnimFrame;
    // if (animTimer < deltaTimeBetweenFrames)
    //     return currentAnimFrame;

    // animTimer = 0;
    // if (currentAnimFrame > 3) {
    //     currentAnimFrame = 0;
    // }
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
        interpolated[i] =
            glm::mix(frames[currentAnimFrame][i], frames[nextFrame][i],
                     animTimer / deltaTimeBetweenFrames);
    }
    setLegsPosition(interpolated);
    return;
};

void Character::setLegsPosition(glm::fvec4 position) {
    printf("moving legs to %f %f %f %f\n", position[0], position[1],
           position[2], position[3]);
    legRotation = position;
    for (int i = 0; i < 4; i++) {
        legRotation[i] = position[i];
        if (this->currentHeading == Heading::LEFT) {
            legRotation[i] *= -1;
        }
    }
}
