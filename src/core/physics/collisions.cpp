#include "collisions.h"

bool handleCollision(const std::shared_ptr<PhysicsEntity> &entity1,
                            const std::shared_ptr<PhysicsEntity> &entity2,
                            bool set_collided, bool resolve) {
    if (entity1->getHitbox()->empty() || entity2->getHitbox()->empty()) {
        return false;
    }

    bool collided = entity1->getHitbox()->collides(*entity2->getHitbox());

    if (collided && resolve) {
        entity1->resolveCollision(*entity2);
    }

    if (set_collided && collided) {
        entity1->setCollided();
        entity2->setCollided();
    }

    return collided;
}

bool handleCollision(const std::shared_ptr<Ray> &ray, const std::shared_ptr<PhysicsEntity> &entity,
                            bool set_collided) {
    if (entity->getHitbox()->empty()) {
        return false;
    }

    bool collided = ray->collides(*entity->getHitbox());

    if (set_collided && collided) {
        entity->setCollided();
    }

    return collided;
}