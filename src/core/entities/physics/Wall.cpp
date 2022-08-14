#include "Wall.h"

Wall::Wall(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize,
           std::shared_ptr<std::map<std::string, Animation>> animation_group, float mass, bool is_static)
        : PhysicsEntity(position, std::move(camera), viewSize, std::move(animation_group), mass, is_static) {

}
