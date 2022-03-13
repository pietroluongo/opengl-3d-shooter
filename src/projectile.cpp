#include "../include/projectile.h"
#include "../include/enemy.h"
#include "../include/globalCtx.h"

#if defined(_WIN32) || defined(WIN32)
#define M_PI 3.14159265358979323846
#endif

extern GlobalCtx* context;

Projectile::Projectile(float x, float y, float z, float size, float angle,
                       ProjectileType type, float speed)
    : Object(x, y, z, size) {
    this->angle = angle;
    this->getCollider()->resize(size, size / 2, size / 2);
    this->setIsAffectedByGravity(false);
    this->speed = speed;
    this->type = type;
}

Projectile::~Projectile() {}

void Projectile::draw() {
    glfvec2 position = this->getPosition();
    glPushMatrix();
    glTranslatef(position.x, position.y, 0);
    glRotatef(this->angle * 180 / M_PI, 0, 0, 1);
    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(0, 0);
    glVertex2f(this->size, 0);
    glVertex2f(this->size, this->size / 2);
    glVertex2f(0, this->size / 2);

    glEnd();
    glPopMatrix();
}

void Projectile::idle() {
    bool hasThisBeenDeleted = this->checkCollisions();
    if (hasThisBeenDeleted) {
        return;
    }
    this->moveX(cos(this->angle) * this->speed);
    this->moveY(sin(this->angle) * this->speed);
    this->moveZ(10);
    this->collider->idle();
    this->Object::idle();
    glm::fvec4 worldBounds = context->getGameRef()->getMap()->getWorldBounds();
    if (this->getPosition().x < worldBounds[0] ||
        this->getPosition().x > worldBounds[1] ||
        this->getPosition().y < worldBounds[2] ||
        this->getPosition().y > worldBounds[3]) {
        context->getGameRef()->deleteProjectile(*this);
    }
}

void Projectile::setPosition(glfvec2 position) {
    this->Object::setPosition(position);
}

void Projectile::setPosition(GLfloat x, GLfloat y) {
    this->Object::setPosition(x, y);
}

bool Projectile::checkCollisions() {
    std::vector<Platform*> platforms =
        context->getGameRef()->getMap()->getPlatforms();
    for (auto platform : platforms) {
        if (this->collider->overlaps(platform->getCollider())) {
            context->getGameRef()->deleteProjectile(*this);
            return true;
        }
    }
    if (this->type == PROJECTILE_TYPE_PLAYER) {
        auto enemies = context->getGameRef()->getEnemies();
        for (auto enemy : enemies) {
            if (this->collider->overlaps(enemy->getCollider())) {
                context->getGameRef()->deleteProjectile(*this);
                context->getGameRef()->deleteEnemy(*enemy);
                return true;
            }
        }
    } else {
        Player* player = context->getGameRef()->getPlayer();
        if (this->collider->overlaps(player->getCollider())) {
            context->getGameRef()->deleteProjectile(*this);
            player->kill();
            return true;
        }
    }
    return false;
}

std::vector<std::vector<Collider*>*> Projectile::colliders() { return {}; }