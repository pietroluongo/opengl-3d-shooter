#include "../include/projectile.h"
#include "../include/globalCtx.h"

extern GlobalCtx* context;

Projectile::Projectile(float x, float y, float size, float angle)
    : Object(x, y) {
    this->collider =
        new Collider(x, y, size, size, this, pivotPosition::CENTER);
    this->size = size;
    this->angle = angle;
}

Projectile::~Projectile() { (this->collider); }

void Projectile::draw() {
    glPushMatrix();
    glTranslatef(this->position.x, this->position.y, 0);
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    for (int i = 0; i < 360; i++) {
        glVertex2f(cos(i) * this->size, sin(i) * this->size);
    }
    glEnd();
    glPopMatrix();
}

void Projectile::idle() {
    this->collider->idle();
    this->position.x += cos(this->angle) * 10 * context->getDeltaTime();
    this->position.y += sin(this->angle) * 10 * context->getDeltaTime();
    glm::fvec4 worldBounds = context->getGameRef()->getMap()->getWorldBounds();
    if (this->position.x < worldBounds[0] ||
        this->position.x > worldBounds[1] ||
        this->position.y < worldBounds[2] ||
        this->position.y > worldBounds[3]) {
        context->getGameRef()->deleteProjectile(this);
    }
}

void Projectile::moveX(double) {}
void Projectile::moveY(double) {}

void Projectile::setPosition(glfvec2 position) {
    this->Object::setPosition(position);
}

void Projectile::setPosition(GLfloat x, GLfloat y) {
    this->Object::setPosition(x, y);
}
void Projectile::accelerateX(double amount){};
void Projectile::accelerateY(double amount){};