#ifndef GAMEENGINE_COLLISIONS_H
#define GAMEENGINE_COLLISIONS_H

#include "../entities/physics/PhysicsEntity.h"

bool handleCollision(const std::shared_ptr<PhysicsEntity> &entity1, const std::shared_ptr<PhysicsEntity> &entity2,
                     bool set_collided = true, bool resolve = true);

bool handleCollision(const std::shared_ptr<Ray> &ray, const std::shared_ptr<PhysicsEntity> &entity,
                     bool set_collided = true);

#endif //GAMEENGINE_COLLISIONS_H
