#include "../include/player.h"
#include "../include/globalCtx.h"
#include "../include/keymap.h"
#include "../libs/glm/gtc/matrix_transform.hpp"
#include "../libs/glm/gtc/type_ptr.hpp"
#include <cmath>
#include <string>
#include <vector>

#if defined(_WIN32) || defined(WIN32)
#define M_PI 3.14159265358979323846
#endif

extern GlobalCtx* context;

float limitArmMovement(float angle);

Player::Player(GLfloat x, GLfloat y, GLfloat z, GLfloat size,
               CharacterDrawMode mode)
    : Character(x, y, z, size) {
    this->armPosition = 0.2 * size;
    this->armWidth = 0.04 * size;
    this->armHeight = 0.4 * size;
    this->collider->resize(size * 0.2, size, size);
    this->drawMode = mode;
    if (mode == CHARACTER_3D) {
        this->mouseMode = MOUSE_MODE_SINGLE_AXIS;
    } else {
        this->mouseMode = MOUSE_MODE_DUAL_AXIS;
    }
    this->head = std::unique_ptr<Sphere>(new Sphere(0.1 * size, 20));
}

Player::~Player() {}

void Player::draw() {
    this->head->setTexture(context->getTexture("head.bmp"));
    glfvec3 position = this->getPosition();
    glPushMatrix();
    glTranslatef(position.x, position.y, position.z);
    glRotatef(this->visualRotation.x, 1, 0, 0);
    glRotatef(this->visualRotation.y, 0, 1, 0);
    glRotatef(this->visualRotation.z, 0, 0, 1);
    drawCoordinateSystem();
    glColor3f(0.0f, 1.0f, 1.0f);
    this->drawChest();
    glColor3f(1.0f, 1.0f, 1.0f);
    if (context->getGameRef()->getMainCamera()->getCameraBehaviour() !=
        CameraBehaviour::CAMERA_FPS) {
        this->drawHead();
    }
    glTranslatef(0, -this->size * 0.3f, 0);
    this->drawLegs();
    glColor3f(1.0f, 0.0f, 0.0f);
    this->drawArm();

    if (context->shouldObjectsDrawCoordinateSystem) {
        this->drawAxis();
    }
    glPopMatrix();
    if (context->shouldObjectsDrawColliders)
        this->collider->draw();
    {
        glm::mat4 t = glm::mat4(1.0);
        glm::fvec4 position = glm::fvec4{0, 0, 0, 1};
        t = glm::translate(
            t, glm::vec3(this->getPosition().x,
                         this->getPosition().y - this->size * 0.3 + armPosition,
                         this->getPosition().z));
        t = glm::rotate(t, (float)(this->visualRotation.y * M_PI / 180),
                        glm::vec3(0, 1, 0));
        t = glm::rotate(t, (float)(this->armAngle * M_PI / 180),
                        glm::vec3(0, 0, 1));

        t = glm::translate(t,
                           glm::vec3(0, this->armHeight + 0.2 * this->size, 0));

        position = t * position;
        glColor3f(1, 0, 0);
        glPushMatrix();
        glDisable(GL_LIGHTING);
        glMultMatrixf(glm::value_ptr(t));
        glPointSize(15.0f);
        glBegin(GL_POINTS);
        glVertex3f(0, 0, 0);
        glEnd();
        glEnable(GL_LIGHTING);
        glPopMatrix();
    }
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
        this->rotateY(1 * this->size);
    }
    if (context->isKeyPressed(keymap::MOVE_LEFT_BUTTON)) {
        this->isRequestingMove = true;
        this->rotateY(-1 * this->size);
    }

    if (context->isKeyPressed(keymap::JUMP_BUTTON) ||
        context->getIsPressingRMB()) {
        this->isRequestingJump = true;
    } else {
        this->isRequestingJump = false;
    }

    if (context->isKeyPressed(keymap::MOVE_FORWARD_BUTTON)) {
        this->isRequestingMove = true;
        this->moveForward(2.5 * this->size);
    }
    if (context->isKeyPressed(keymap::MOVE_BACKWARD_BUTTON)) {
        this->isRequestingMove = true;
        this->moveForward(-2.5 * this->size);
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
    if (this->mouseMode == MOUSE_MODE_DUAL_AXIS) {
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
    } else {
        glm::fvec2 mousePos = context->getNormalizedMousePos();
        this->armAngle = -90 + (90 / 2 * mousePos.y);
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
    glm::mat4 t = glm::mat4(1.0);
    glm::fvec4 position = glm::fvec4{0, 0, 0, 1};
    t = glm::translate(
        t, glm::vec3(this->getPosition().x,
                     this->getPosition().y - this->size * 0.3 + armPosition,
                     this->getPosition().z));
    t = glm::rotate(t, (float)(this->visualRotation.y * M_PI / 180),
                    glm::vec3(0, 1, 0));
    t = glm::rotate(t, (float)(this->armAngle * M_PI / 180),
                    glm::vec3(0, 0, 1));

    t = glm::translate(t, glm::vec3(0, this->armHeight + 0.2 * this->size, 0));

    position = t * position;

    context->getGameRef()->createProjectile(
        position.x, position.y, position.z, 0.1 * this->size,
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

glm::fvec3 Player::getEyePosition() {
    return glm::fvec3(this->getPosition().x,
                      this->getPosition().y - 0.3 * this->size,
                      this->getPosition().z);
}

glm::fvec3 Player::getDollyPosition() {
    glm::mat4 t(1.0);
    glm::fvec3 rot = this->getVisualRotation();
    rot *= M_PI / 180;
    t = glm::translate(t, this->getPosition());
    t = glm::rotate(t, rot.y, glm::fvec3(0, 1, 0));
    t = glm::translate(t, glm::fvec3(-20, -this->size, 0));
    return t * glm::fvec4(1, 1, 1, 1.0);
}

glm::fvec3 Player::getGunPosition() {
    glm::mat4 t = glm::mat4(1.0);
    glm::fvec4 position = glm::fvec4{0, 0, 0, 1};
    t = glm::translate(
        t, glm::vec3(this->getPosition().x,
                     this->getPosition().y - this->size * 0.3 + armPosition,
                     this->getPosition().z));
    t = glm::rotate(t, (float)(this->visualRotation.y * M_PI / 180),
                    glm::vec3(0, 1, 0));
    t = glm::rotate(t, (float)(this->armAngle * M_PI / 180),
                    glm::vec3(0, 0, 1));

    t = glm::translate(t, glm::vec3(0, this->armHeight + 0.2 * this->size, 0));

    position = t * position;
    return position;
}