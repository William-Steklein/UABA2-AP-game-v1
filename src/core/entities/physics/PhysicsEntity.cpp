#include "PhysicsEntity.h"

PhysicsEntity::PhysicsEntity(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize,
                             std::shared_ptr<std::map<std::string, Animation>> animation_group)
        : Entity(position, std::move(camera), viewSize, std::move(animation_group)) {

}
