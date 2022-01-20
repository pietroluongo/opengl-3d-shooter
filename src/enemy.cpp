#include "../include/enemy.h"
#include "../include/globalCtx.h"
#include <GL/gl.h>
#include <cmath>

extern GlobalCtx* context;

Enemy::Enemy(GLfloat x, GLfloat y, GLfloat size) : Character(x, y, size) {
    this->setSize(size);
    this->armPosition = 0.2 * size;
    this->armWidth = 0.04 * size;
    this->armHeight = 0.4 * size;
}

Enemy::~Enemy() { delete (this->collider); }

void Enemy::draw() {
    char* tmpString;
    glColor3f(1.0f, 1.0f, 1.0f);
    sprintf(context->textBuffer, "Inimigo");
    tmpString = context->textBuffer;
    glRasterPos2f(this->position.x - 1, this->position.y - 4);
    while (*tmpString) {
        glutBitmapCharacter(context->font, *tmpString);
        tmpString++;
    }
    sprintf(context->textBuffer, "[%.2f, %.2f]", this->position.x,
            this->position.y);
    tmpString = context->textBuffer;

    glRasterPos2f(this->position.x - 1, this->position.y - 3);
    while (*tmpString) {
        glutBitmapCharacter(context->font, *tmpString);
        tmpString++;
    }

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

void Enemy::idle() {
    this->collider->idle();
    this->updateArmAngle();

    if (!this->isGrounded) {
        if (this->wasGrounded) {
            this->moveDirection *= -1;
            this->position.x += this->moveDirection;
            return;
        }
        this->position.y += 0.01;
    }

    // glm::fvec2 delta = {10 * context->getDeltaTime() * moveDirection, 0};
    // this->position += delta;
}

void Enemy::updateArmAngle() {
    glm::fvec2 playerPos = context->getGameRef()->getPlayer()->getPosition();
    this->armAngle =
        atan2(playerPos.y - this->position.y, playerPos.x - this->position.x) *
            180 / M_PI -
        90;
}