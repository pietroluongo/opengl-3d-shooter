#include "../include/projectile.h"
#include "../include/globalCtx.h"

extern GlobalCtx* context;

Projectile::Projectile(float x, float y, float size, float angle)
    : Object(x, y, size) {
    this->angle = angle;
    this->setIsAffectedByGravity(false);
}

Projectile::~Projectile() { delete (this->collider); }

void Projectile::draw() {
    glfvec2 position = this->getPosition();
    glPushMatrix();
    glTranslatef(position.x, position.y, 0);
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        glVertex2f(cos(i) * this->size, sin(i) * this->size);
    }
    glEnd();
    glPopMatrix();
}

void Projectile::idle() {
    this->checkCollisions();
    this->moveX(cos(this->angle) * 20);
    this->moveY(sin(this->angle) * 20);
    this->collider->idle();
    this->Object::idle();
    glm::fvec4 worldBounds = context->getGameRef()->getMap()->getWorldBounds();
    if (this->getPosition().x < worldBounds[0] ||
        this->getPosition().x > worldBounds[1] ||
        this->getPosition().y < worldBounds[2] ||
        this->getPosition().y > worldBounds[3]) {
        context->getGameRef()->deleteProjectile(this);
    }
}

void Projectile::setPosition(glfvec2 position) {
    this->Object::setPosition(position);
}

void Projectile::setPosition(GLfloat x, GLfloat y) {
    this->Object::setPosition(x, y);
}

void Projectile::checkCollisions() {
    std::vector<Platform*> platforms =
        context->getGameRef()->getMap()->getPlatforms();
    std::vector<Enemy*> enemies = context->getGameRef()->getEnemies();
    for (auto platform : platforms) {
        if (this->collider->overlaps(platform->getCollider())) {
            context->getGameRef()->deleteProjectile(this);
        }
    }
    for (auto enemy : enemies) {
        if (this->collider->overlaps(enemy->getCollider())) {
            context->getGameRef()->deleteEnemy(enemy);
            context->getGameRef()->deleteProjectile(this);
        }
    }
}

const char* Projectile::debug() { return "ok i'm alive\n"; }