#ifndef CHARACTER_H
#define CHARACTER_H

#include "collider.h"
#include "object.h"

enum AnimState { IDLE, WALKING, JUMPING, DEAD };

enum Heading { LEFT, RIGHT };

class Character : public Object {
  protected:
    float armHeight;
    float armPosition;
    float armWidth;
    int health = 100;
    Heading currentHeading = RIGHT;
    AnimState currentAnimState = AnimState::IDLE;
    const double animDelta = 0.1;

    void drawArm();
    void drawLegs();
    void drawHead();
    void drawChest();
    void drawGun();

    bool isJumping = false;
    bool isFalling = false;

    glm::fvec4 walkingFrames[2] = {{25, 20, 10, 30}, {-10, 5, -25, 20}};
    glm::fvec4 jumpingFrames[2] = {{30, 50, 0, 50}, {20, 60, 10, 100}};

    int currentAnimFrame = 0;
    int curAnimCounter = 0;

    /**
     * @brief Controls the player's leg rotation
     * [0] - Left leg
     * [1] - Left knee
     * [2] - Right leg
     * [3] - Right knee
     */
    glm::fvec4 legRotation = {25, 20, 10, 30};

  public:
    // Public for debug reasons
    float armAngle = 0.0f;
    double animTimer = 0;

    Character(GLfloat x, GLfloat y, GLfloat size) : Object(x, y, size){};
    virtual void draw() = 0;
    virtual void idle() = 0;
    virtual void applyDamage(int damage) { health -= damage; }
    virtual void updateArmAngle() = 0;

    void setSize(float size) {
        this->size = size;
        handleResize();
    }

    void handleResize();

    const char* getCurrentAnimState() {
        switch (this->currentAnimState) {
        case AnimState::IDLE:
            return "IDLE";
        case AnimState::WALKING:
            return "WALKING";
        case AnimState::JUMPING:
            return "JUMP";
        case AnimState::DEAD:
            return "DEAD";
        }
        return "ERROR";
    };
    float* getLegRotation() { return &this->legRotation[0]; };
    void nextAnimFrame();
    void setHeading(Heading heading) { this->currentHeading = heading; };
    const char* getHeading() {
        switch (this->currentHeading) {
        case LEFT:
            return "LEFT";
        case RIGHT:
            return "RIGHT";
        default:
            return "ERROR";
        }
    }

    void setLegsPosition(glm::fvec4 position);
    float* tmp_getSize() { return &this->size; };
};

#endif