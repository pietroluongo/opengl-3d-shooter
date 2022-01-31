#include "../include/enemy.h"
#include "../include/globalCtx.h"
#include <GL/gl.h>
#include <cmath>
#include <cstdlib>

extern GlobalCtx* context;

Enemy::Enemy(GLfloat x, GLfloat y, GLfloat size) : Character(x, y, size) {
    this->setSize(size);
    this->armPosition = 0.2 * size;
    this->armWidth = 0.04 * size;
    this->armHeight = 0.4 * size;
    this->teleportToGround();
    this->getCollider()->resize(size * 0.2, size);
    this->targetShootTimer = rand() % 1000 / 100;
    this->currentAnimState = AnimState::WALKING;
}

Enemy::~Enemy() { delete (this->collider); }

void Enemy::draw() {
    glfvec2 position = this->getPosition();

    glPushMatrix();
    glTranslatef(position.x, position.y, 0.0f);

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
    if (context->shouldEnemiesDrawInfo) {

        char* tmpString;
        glColor3f(1.0f, 1.0f, 1.0f);
        sprintf(context->textBuffer, "Inimigo");
        tmpString = context->textBuffer;
        glRasterPos2f(position.x - 1, position.y - 6);
        while (*tmpString) {
            glutBitmapCharacter(context->font, *tmpString);
            tmpString++;
        }
        sprintf(context->textBuffer, "[%.2f, %.2f]", position.x, position.y);
        tmpString = context->textBuffer;

        glRasterPos2f(position.x - 1, position.y - 5);
        while (*tmpString) {
            glutBitmapCharacter(context->font, *tmpString);
            tmpString++;
        }
        sprintf(context->textBuffer, "Shoot: %.2f",
                this->targetShootTimer - this->enemyShootTimer);
        tmpString = context->textBuffer;

        glRasterPos2f(position.x - 1, position.y - 4);
        while (*tmpString) {
            glutBitmapCharacter(context->font, *tmpString);
            tmpString++;
        }
    }
}

void Enemy::idle() {
    this->enemyShootTimer += context->getDeltaTime();
    if (this->enemyShootTimer >= this->targetShootTimer) {
        this->enemyShootTimer = 0;
        this->targetShootTimer = rand() % 600 / 100 + 1;
        this->shoot();
    }
    this->Object::idle();
    this->updateArmAngle();
    if (this->getCollisionArr()[3]) {
        this->wasGrounded = true;
    }
    if (this->getCollisionArr()[0]) {
        this->moveDirection = 1;
        this->setHeading(Heading::RIGHT);
    } else if (this->getCollisionArr()[1]) {
        this->moveDirection = -1;
        this->setHeading(Heading::LEFT);
    }

    if (!this->isGrounded) {
        if (this->wasGrounded) {
            this->wasGrounded = false;
            this->moveDirection *= -1;
            this->teleport(this->getPosition().x + (moveDirection),
                           this->getPosition().y);
        }
    }
    this->moveX(this->moveDirection * 10);
}

void Enemy::updateArmAngle() {
    glfvec2 position = this->getPosition();
    glm::fvec2 playerPos = context->getGameRef()->getPlayer()->getPosition();
    this->armAngle =
        atan2(playerPos.y - position.y, playerPos.x - position.x) * 180 / M_PI -
        90;
    if ((this->armAngle >= 45 && this->armAngle <= 90) ||
        this->armAngle <= -225) {
        this->setHeading(LEFT);
    } else {
        this->setHeading(RIGHT);
    }
}

void Enemy::shoot() {
    glfvec2 position = this->getPosition();
    context->getGameRef()->createProjectile(
        position.x + (this->armHeight * sin(-this->armAngle * M_PI / 180)),
        position.y + (this->armHeight * cos(this->armAngle * M_PI / 180)), 0.5,
        (90 + this->armAngle) * M_PI / 180, PROJECTILE_TYPE_ENEMY);
}

void Enemy::kill() {
    context->getGameRef()->deleteEnemy(this);
    this->isAlive = false;
}