#include "../include/enemy.h"
#include "../include/globalCtx.h"
#include <GL/gl.h>
#include <cmath>

extern GlobalCtx* context;

Enemy::Enemy(GLfloat x, GLfloat y, GLfloat size) : Character(x, y, size) {
    this->setSize(size);
}

Enemy::~Enemy() { delete (this->collider); }

void Enemy::drawChest() {
    glBegin(GL_QUADS);
    glVertex2f(-this->size / 4, -this->size / 2);
    glVertex2f(this->size / 4, -this->size / 2);
    glVertex2f(this->size / 4, this->size / 2);
    glVertex2f(-this->size / 4, this->size / 2);
    glEnd();
}

void Enemy::drawArm() {
    glPushMatrix();
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
    sprintf(context->textBuffer, "[%.2f, %.2f]", this->speed.x, this->speed.y);
    tmpString = context->textBuffer;

    glRasterPos2f(this->position.x - 1, this->position.y - 2);
    while (*tmpString) {
        glutBitmapCharacter(context->font, *tmpString);
        tmpString++;
    }

    glPushMatrix();
    glTranslatef(this->position.x, this->position.y, 0.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    this->drawChest();
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
    // this->Object::idle();
    // this->updateArmAngle();
    this->collider->idle();
    this->isGrounded = false;
    // this->isGrounded = false;

    std::vector<Platform*> platforms =
        context->getGameRef()->getMap()->getPlatforms();
    for (auto platform : platforms) {
        if (this->collider->collidesLeft(platform->getCollider())) {
            // this->speed.x = 1;
            this->moveDirection = 1;
        }
        if (this->collider->collidesRight(platform->getCollider())) {
            this->moveDirection = -1;
        }
        if (this->collider->collidesVerticallyWith(platform->getCollider())) {
            this->isGrounded = true;
            this->wasGrounded = true;
        }
    }

    if (!this->isGrounded) {
        if (this->wasGrounded) {
            this->moveDirection *= -1;
            this->position.x += this->moveDirection;
            return;
        }
        this->position.y += 0.01;
    }

    // if (!this->isGrounded) {
    //     this->accelerateY(100);
    // }
    // this->accelerateX(250.0f);
    // glm::fvec2 delta = {this->speed.x * context->getDeltaTime(),
    //                     this->speed.y * context->getDeltaTime()};

    // this->position += delta;
    glm::fvec2 delta = {10 * context->getDeltaTime() * moveDirection, 0};
    this->position += delta;
}

void Enemy::updateArmAngle() {
    glm::fvec2 playerPos = context->getGameRef()->getPlayer()->getPosition();
    this->armAngle =
        atan2(playerPos.y - this->position.y, playerPos.x - this->position.x) *
            180 / M_PI -
        90;
}