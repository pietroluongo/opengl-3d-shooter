#ifndef CHARACTER_H
#define CHARACTER_H

#include "collider.h"
#include "object.h"

enum AnimState { IDLE, WALKING, JUMPING, DEAD };

enum Heading { LEFT, RIGHT };

class Character : public Object {
  protected:
    float armHeight = 0.4f * size;
    float armPosition = 0.5f * size;
    float armWidth = 0.05f * size;
    int health = 100;
    Heading currentHeading = RIGHT;
    AnimState currentState = AnimState::IDLE;

    void drawArm();
    void drawLegs();
    void drawHead();
    void drawChest();
    bool isJumping = false;
    bool isFalling = false;

    glm::fvec4 frames[4] = {{20, 35, 10, 20},
                            {21, 35, 4, 15},
                            {-12, 35, -20, 15},
                            {-12, 35, -42, 15}};
    int currentAnimFrame = 0;
    int curAnimCounter = 0;

    /**
     * @brief Controls the player's leg rotation
     * [0] - Left leg
     * [1] - Left knee
     * [2] - Right leg
     * [3] - Right knee
     */
    glm::fvec4 legRotation = {25, 35, 20, 15};

  public:
    // Public for debug reasons
    float armAngle = 0.0f;

    Character(GLfloat x, GLfloat y, GLfloat size) : Object(x, y, size){};
    virtual void draw() = 0;
    virtual void idle() = 0;
    virtual void applyDamage(int damage) { health -= damage; }
    virtual void updateArmAngle() = 0;

    void setSize(float size) {
        this->size = size;
        this->armWidth = 0.1f * size;
        this->armHeight = 0.5f * size;
    }

    const char* getCurrentAnimState() {
        switch (this->currentState) {
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
    int nextAnimFrame();
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
};

#endif