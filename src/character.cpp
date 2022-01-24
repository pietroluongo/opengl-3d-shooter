#include "../include/character.h"
#include "../include/globalCtx.h"

extern GlobalCtx* context;

// glm::fvec4 frames[4] = {
// {25, 20, 10, 30}, {10, 25, 4, 15}, {-10, 10, -20, 30}, {-10, 5, -25, 20}};
glm::fvec4 walkingFrames[2] = {{25, 20, 10, 30}, {-10, 5, -25, 20}};
glm::fvec4 jumpingFrames[2] = {{30, 50, 0, 50}, {20, 60, 10, 100}};
// glm::fvec4 jumpingFrames[2] = {{0, 0, 10, 10}, {-5, 15, -20, 10}};

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
