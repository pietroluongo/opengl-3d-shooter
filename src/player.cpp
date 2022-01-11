#include "../include/player.h"
#include "../include/globalCtx.h"
#include <cmath>
#include <vector>

extern GlobalCtx* context;

static float CHEST_PROPORTION = 0.5f;
static float HEAD_PROPORTION = 0.1f;
static float LEGS_PROPORTION = 0.4f;

float limitArmMovement(float angle);

Player::Player(GLfloat x, GLfloat y, GLfloat size) : Character(x, y, size) {}

Player::~Player() { delete (this->collider); }

void Player::draw() {
    glPushMatrix();
    glTranslatef(this->position.x, this->position.y, 0.0f);
    glColor3f(0.0f, 1.0f, 1.0f);
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

void Player::idle() {
    this->handleMovementKeys();
    this->Object::idle();
    this->updateArmAngle();
    this->collider->idle();
    std::vector<Platform*> platforms =
        context->getGameRef()->getMap()->getPlatforms();
    this->isGrounded = false;
    for (auto platform : platforms) {
        if (this->collider->collidesVerticallyWith(platform->getCollider())) {
            if (context->shouldPlatformsShowCollisions)
                platform->setColor({1.0f, 0, 0});
            if (this->speed.y > 0) {
                this->speed.y = 0;
            }
            this->isGrounded = true;
        } else if (this->collider->collidesLeft(platform->getCollider())) {
            if (context->shouldPlatformsShowCollisions)
                platform->setColor({1.0f, 0, 0});
            this->speed.x = 1;

        } else if (this->collider->collidesRight(platform->getCollider())) {
            if (context->shouldPlatformsShowCollisions)
                platform->setColor({1.0f, 0, 0});
            this->speed.x = -1;
        } else {
            platform->setColor({1.0f, 1.0f, 1.0f});
        }
    }

    std::vector<Enemy*> enemies = context->getGameRef()->getEnemies();
    for (auto enemy : enemies) {
        if (this->collider->collidesVerticallyWith(enemy->getCollider())) {
            this->isGrounded = true;
            if (this->speed.y > 0) {
                this->speed.y = 0;
            }
        }
    }

    if (!this->isGrounded) {
        this->accelerateY(100);
    }

    this->position.x += this->speed.x * context->getDeltaTime();
    this->position.y += this->speed.y * context->getDeltaTime();
    if (this->isGrounded)
        this->isJumping = false;
}

void Player::handleMovementKeys() {
    if (context->isKeyPressed('D') || context->isKeyPressed('d')) {
        this->accelerateX(250.0f);
    }
    if (context->isKeyPressed('A') || context->isKeyPressed('a')) {
        this->accelerateX(-250.0f);
    }

    if (context->isKeyPressed('w') || context->isKeyPressed('W')) {
        this->jump();
    }

    if (context->isKeyPressed('s') || context->isKeyPressed('S')) {
    }

    if (context->isKeyPressed(' ')) {
        // this->shoot();
    }
}

void Player::drawChest() {
    glBegin(GL_QUADS);
    glVertex2f(-this->size / 4, -this->size / 2);
    glVertex2f(this->size / 4, -this->size / 2);
    glVertex2f(this->size / 4, this->size / 2);
    glVertex2f(-this->size / 4, this->size / 2);
    glEnd();
}

void Player::drawArm() {
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
    this->accelerateY(-10000);
}

void Player::shoot() {
    context->getGameRef()->createProjectile(
        this->position.x +
            (this->armHeight * sin(-this->armAngle * M_PI / 180)),
        this->position.y + (this->armHeight * cos(this->armAngle * M_PI / 180)),
        0.5, (90 + this->armAngle) * M_PI / 180);
}