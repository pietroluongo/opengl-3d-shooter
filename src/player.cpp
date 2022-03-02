#include "../include/player.h"
#include "../include/globalCtx.h"
#include "../include/keymap.h"
#include <cmath>
#include <string>
#include <vector>

#if defined(_WIN32) || defined(WIN32)
#define M_PI 3.14159265358979323846
#endif

extern GlobalCtx* context;

float limitArmMovement(float angle);

Player::Player(GLfloat x, GLfloat y, GLfloat size, CharacterDrawMode mode)
    : Character(x, y, size) {
    this->armPosition = 0.2 * size;
    this->armWidth = 0.04 * size;
    this->armHeight = 0.4 * size;
    this->collider->resize(size * 0.2, size);
    this->drawMode = mode;
    this->head = std::unique_ptr<Sphere>(new Sphere(0.1 * size, 10));
}

Player::~Player() {}

void Player::draw() {
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
}

void Player::idle() {
    this->isRequestingMove = false;
    if (this->getCollisionArr()[3]) {
        this->isGrounded = true;
        this->hasHitHead = false;
    }
    if (this->getCollisionArr()[2]) {
        this->hasHitHead = true;
    }
    this->Object::idle();
    this->handleMovementKeys();
    this->updateAnimState();
    this->handleJump();
    this->updateArmAngle();
    if (this->getPosition().x >=
        context->getGameRef()->getMap()->getWorldBounds()[1] -
            (this->size / 8)) {
        context->getGameRef()->setState(GameState::WON);
    }
}

void Player::handleMovementKeys() {
    if (context->isKeyPressed(keymap::MOVE_RIGHT_BUTTON)) {
        this->isRequestingMove = true;
        this->moveX(2.5 * this->size);
    }
    if (context->isKeyPressed(keymap::MOVE_LEFT_BUTTON)) {
        this->isRequestingMove = true;
        this->moveX(-2.5 * this->size);
    }

    if (context->isKeyPressed(keymap::MOVE_UP_BUTTON) ||
        context->getIsPressingRMB()) {
        this->isRequestingJump = true;
    } else {
        this->isRequestingJump = false;
    }

    if (context->getIsPressingLMB()) {
        if (!isRequestingFire) {
            this->shoot();
            isRequestingFire = true;
        }
    } else {
        isRequestingFire = false;
    }
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
    glfvec2 position = this->getPosition();
    float dy = position.y - mousePos.y;
    float dx = position.x - mousePos.x;
    this->armAngle = atan2(-dy, -dx) * 180 / M_PI - 90;
    this->armAngle = limitArmMovement(this->armAngle);
    if ((this->armAngle >= 45 && this->armAngle <= 90) ||
        this->armAngle <= -225) {
        this->setHeading(LEFT);
    } else {
        this->setHeading(RIGHT);
    }
}

void Player::handleJump() {
    if (this->isRequestingJump) {
        this->wasRequestingJump = true;
    }
    if (this->isGrounded) {
        jumpTime = 0;
        this->wasRequestingJump = false;
        shouldIncreaseHeight = true;
        this->setIsAffectedByGravity(false);
    }
    if (this->jumpTime >= 1 || this->hasHitHead) {
        this->setIsAffectedByGravity(true);
    }
    if (!this->isGrounded && !this->isRequestingJump) {
        this->setIsAffectedByGravity(true);
    }
    if ((this->wasRequestingJump && !this->isRequestingJump) ||
        this->hasHitHead || (this->fallTimer > 0 && !this->isRequestingJump)) {
        shouldIncreaseHeight = false;
    }
    if (this->isRequestingJump && this->jumpTime < 1 && shouldIncreaseHeight) {
        this->moveY(-2.5 * this->size);
    }
    this->jumpTime += context->getDeltaTime();
}

void Player::shoot() {
    glfvec2 position = this->getPosition();

    glfvec2 firePosition = {0, 0};
    firePosition.x = position.x - ((this->armHeight + 0.2 * this->size) *
                                   sin(this->armAngle * M_PI / 180));
    firePosition.y = (position.y - 0.2 * this->size) +
                     ((this->armHeight + 0.2 * this->size) *
                      cos(this->armAngle * M_PI / 180));
    context->getGameRef()->createProjectile(
        firePosition.x, firePosition.y, 0.1 * this->size,
        (90 + this->armAngle) * M_PI / 180, PROJECTILE_TYPE_PLAYER,
        5 * this->size);
}

void Player::updateAnimState() {
    if (this->isGrounded) {
        if (this->isRequestingMove) {
            this->currentAnimState = AnimState::WALKING;
        } else {

            this->currentAnimState = AnimState::IDLE;
        }
    } else {
        this->currentAnimState = AnimState::JUMPING;
    }
}

void Player::kill() {
    if (this->isInvincible)
        return;
    context->getGameRef()->setState(GameState::OVER);
    this->isAlive = false;
}

std::vector<std::vector<Collider*>*> Player::colliders() {
    return std::vector<std::vector<Collider*>*>{
        context->getGameRef()->getEnemyColliders(),
        context->getGameRef()->getMap()->getPlatformsColliders()};
}