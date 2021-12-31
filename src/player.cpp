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
    this->collider->draw();
}

void Player::idle() {
    canMoveY = true;
    canMoveX = true;
    this->updateArmAngle();
    this->collider->idle();
    std::vector<Platform*> platforms =
        context->getGameRef()->getMap()->getPlatforms();
    for (auto platform : platforms) {
        if (this->collider->collidesVerticallyWith(platform->getCollider())) {
            this->speed.y = 0;
            canMoveY = false;
            break;
        }
        if (this->collider->collidesHorizontallyWith(platform->getCollider())) {
            this->speed.x = 0;
            canMoveX = false;
            break;
        }
    }
    if (canMoveY) {
        this->accelerateY(20.0f);
    }
    this->position.x += this->speed.x * context->getDeltaTime();
    this->position.y += this->speed.y * context->getDeltaTime();
    this->handleMovementKeys();
}

void Player::handleMovementKeys() {
    if (context->isKeyPressed('D') || context->isKeyPressed('d')) {
        // this->moveX(50);
        this->accelerateX(50.0f);
    }
    if (context->isKeyPressed('A') || context->isKeyPressed('a')) {
        // this->moveX(-50);
        this->accelerateX(-50.0f);
    }

    if (context->isKeyPressed('w') || context->isKeyPressed('W')) {
        this->moveY(-50);
        this->accelerateY(-50);
    }

    if (context->isKeyPressed('s') || context->isKeyPressed('S')) {
        // this->moveY(50);
        this->accelerateY(50);
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
    glBegin(GL_LINES);
    glVertex2f(this->position.x, this->position.y);
    glVertex2f(mousePos.x, mousePos.y);
    glEnd();
}