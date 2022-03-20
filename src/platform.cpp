#include "../include/platform.h"
#include "../include/constants.h"
#include "../include/globalCtx.h"
#include "../include/solidUtils.h"
#include <cstdio>

extern GlobalCtx* context;

Platform::Platform(float x, float y, float w, float h, PlatformType type,
                   pivotPosition pivot) {
    this->position = glfvec2(x, y);
    this->width = w;
    this->height = h;
    this->pivot = pivot;
    // Z = 0 for all platforms
    this->collider = std::unique_ptr<Collider>(
        new Collider(x, y, 0, w, h, 1, nullptr, pivot));
}

Platform::~Platform() {}

void Platform::draw() {
    glPushMatrix();
    glTranslatef(this->position.x, this->position.y, 0);
    glColor3f(this->color.r, this->color.g, this->color.b);
    if (context->getGameRef()->getCurrentRenderMode() == RenderMode::D2) {
        glBegin(GL_QUADS);
        switch (this->pivot) {
        case pivotPosition::CENTER:
            glVertex2f(-this->width / 2, -this->height / 2);
            glVertex2f(this->width / 2, -this->height / 2);
            glVertex2f(this->width / 2, this->height / 2);
            glVertex2f(-this->width / 2, this->height / 2);
            break;
        case pivotPosition::BOT_LEFT:
            glVertex2f(0, -this->height);
            glVertex2f(this->width, -this->height);
            glVertex2f(this->width, 0);
            glVertex2f(0, 0);
            break;
        case pivotPosition::TOP_LEFT:
            glVertex2f(0, 0);
            glVertex2f(0, this->height);
            glVertex2f(this->width, this->height);
            glVertex2f(this->width, 0);
        }
        glEnd();

        if (context->shouldObjectsDrawCoordinateSystem) {
            this->drawAxis();
        }
    } else {
        // top left
        glm::fvec3 vecs[4] = {
            glm::fvec3(0, 0, 0),
            glm::fvec3(0, this->height, 0),
            glm::fvec3(this->width, this->height, 0),
            glm::fvec3(this->width, 0, 0),
        };
        drawCubeFromExtrude(this->depth, this->color, vecs, this->textureData);
    }

    glPopMatrix();

    if (context->shouldObjectsDrawColliders)
        this->collider->draw();
}

void Platform::drawAxis() {

    glColor3f(1.0f, 1.0f, 1.0f);
    glPointSize(DEBUG_CENTER_POINT_SIZE);
    glBegin(GL_POINTS);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(DEBUG_AXIS_SIZE, 0.0f, 0.0f);

    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, DEBUG_AXIS_SIZE, 0.0f);

    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, DEBUG_AXIS_SIZE);
    glEnd();
}

Collider* Platform::getCollider() { return this->collider.get(); }

void Platform::setColor(glfvec3 color) { this->color = color; }

void Platform::setDepth(float depth) {
    this->depth = depth;
    this->collider->resize(this->width, this->height, depth);
}

void Platform::updateTextures() {
    switch (this->type) {
    case PlatformType::PLATFORM_BOTTOM:
        this->textureData.top = context->getTexture("grass.bmp");
        this->textureData.bottom = context->getTexture("grass.bmp");
        this->textureData.left = context->getTexture("grass.bmp");
        this->textureData.right = context->getTexture("grass.bmp");
        this->textureData.front = context->getTexture("grass.bmp");
        this->textureData.back = context->getTexture("grass.bmp");
        this->textureData.topScale = 0.05;
        this->textureData.bottomScale = 1;
        this->textureData.leftScale = 1;
        this->textureData.rightScale = 1;
        this->textureData.frontScale = 1;
        this->textureData.backScale = 1;
        break;
    case PlatformType::PLATFORM_TOP:
        this->textureData.top = context->getTexture("grass.bmp");
        this->textureData.bottom = context->getTexture("grass.bmp");
        this->textureData.left = context->getTexture("grass.bmp");
        this->textureData.right = context->getTexture("grass.bmp");
        this->textureData.front = context->getTexture("grass.bmp");
        this->textureData.back = context->getTexture("grass.bmp");
        this->textureData.topScale = 0.05;
        this->textureData.bottomScale = 1;
        this->textureData.leftScale = 1;
        this->textureData.rightScale = 1;
        this->textureData.frontScale = 1;
        this->textureData.backScale = 1;
        break;
    case PlatformType::PLATFORM_LEFT:
    case PlatformType::PLATFORM_RIGHT:
        this->textureData.top = context->getTexture("grass.bmp");
        this->textureData.topScale = 0.05;
        this->textureData.bottom = context->getTexture("grass.bmp");
        this->textureData.left = context->getTexture("wall.bmp");
        this->textureData.right = context->getTexture("wall.bmp");
        this->textureData.front = context->getTexture("wall.bmp");
        this->textureData.back = context->getTexture("wall.bmp");
        break;
    case PlatformType::PLATFORM_GENERIC:
    default:
        this->textureData.top = context->getTexture("grass.bmp");
        this->textureData.topScale = 0.05;
        this->textureData.bottom = context->getTexture("grass.bmp");
        this->textureData.left = context->getTexture("wall.bmp");
        this->textureData.right = context->getTexture("wall.bmp");
        this->textureData.front = context->getTexture("wall.bmp");
        this->textureData.back = context->getTexture("wall.bmp");
        break;
    }
}