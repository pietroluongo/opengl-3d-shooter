#include "../include/player.h"
#include "../include/globalCtx.h"
#include <cmath>
#include <vector>

extern GlobalCtx* context;

// TODO: move this to class header!
glm::fvec4 frames[4] = {
    {20, 35, 10, 20}, {21, 35, 4, 15}, {-12, 35, -20, 15}, {-12, 35, -42, 15}};
int currentAnimFrame = 0;
int curAnimCounter = 0;

float limitArmMovement(float angle);

Player::Player(GLfloat x, GLfloat y, GLfloat size) : Character(x, y, size) {
    this->armPosition = 0.2 * size;
    this->armWidth = 0.04 * size;
    this->armHeight = 0.4 * size;
}

Player::~Player() { delete (this->collider); }

void Player::draw() {
    glPushMatrix();
    glTranslatef(this->position.x, this->position.y, 0.0f);
    glColor3f(0.0f, 1.0f, 1.0f);
    this->drawChest();
    glColor3f(1.0f, 1.0f, 1.0f);
    this->drawHead();
    this->drawLegs();
    glColor3f(1.0f, 0.0f, 0.0f);
    this->drawArm();

    if (context->shouldObjectsDrawCoordinateSystem) {
        this->drawAxis();
    }
    glPopMatrix();
    if (context->shouldObjectsDrawColliders)
        this->collider->draw();
}

void Player::idle() {
    this->collisionDirections = {false, false, false, false};
    this->handleMovementKeys();
    this->Object::idle();
    this->updateArmAngle();
    this->collider->idle();
    this->isGrounded = false;

    if (this->isGrounded)
        this->isJumping = false;

    this->updateAnimState();
}

void Player::handleMovementKeys() {
    if (context->isKeyPressed('D') || context->isKeyPressed('d')) {
        this->moveX(10);
    }
    if (context->isKeyPressed('A') || context->isKeyPressed('a')) {
        this->moveX(-10);
    }

    if (context->isKeyPressed('w') || context->isKeyPressed('W')) {
        this->jump();
    }

    if (context->isKeyPressed('s') || context->isKeyPressed('S')) {
    }

    if (context->isKeyPressed(' ')) {
    }
}

void Player::drawChest() {
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

void Player::drawArm() {
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

float limitArmMovement(float angle) {
    if (angle > -45 && angle < 0) {
        return -45;
    } else if (angle < -135 && angle > -180) {
        return -135;
    } else if (angle < -180 && angle > -225) {
        return -225;
    } else if (angle < 45 && angle > 0) {
        return 45;
    }
    return angle;
}

void Player::updateArmAngle() {
    glm::fvec2 mousePos = context->getWorldSpaceMousePos();
    this->armAngle =
        atan2(mousePos.y - this->position.y, mousePos.x - this->position.x) *
            180 / M_PI -
        90;
    this->armAngle = limitArmMovement(this->armAngle);
}

void Player::jump() {
    if (this->isJumping) {
        return;
    }
    this->isJumping = true;
}

void Player::shoot() {
    context->getGameRef()->createProjectile(
        this->position.x +
            (this->armHeight * sin(-this->armAngle * M_PI / 180)),
        this->position.y + (this->armHeight * cos(this->armAngle * M_PI / 180)),
        0.5, (90 + this->armAngle) * M_PI / 180);
}

void Player::updateAnimState() { this->currentState = AnimState::IDLE; }

void Player::drawHead() {
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

void Player::drawLegs() {
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

int Player::nextAnimFrame() {
    curAnimCounter++;
    if (this->currentState == AnimState::IDLE) {
        for (int i = 0; i < 4; i++) {
            this->legRotation[i] = frames[0][i];
        }
        return 0;
    }
    if (curAnimCounter < 10)
        return currentAnimFrame;
    curAnimCounter = 0;
    currentAnimFrame++;
    if (currentAnimFrame > 3) {
        currentAnimFrame = 0;
    }
    for (int i = 0; i < 4; i++) {
        this->legRotation[i] = frames[currentAnimFrame][i];
    }
    return currentAnimFrame;
};