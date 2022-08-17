#include "PortalRadio.h"

#include <utility>

PortalRadio::PortalRadio(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize,
                         std::shared_ptr<std::map<std::string, AnimationPlayer>> animationGroup, float mass,
                         bool isStatic) : PhysicsEntity(position, std::move(camera), viewSize,
                                                        std::move(animationGroup), mass, isStatic) {
    _hitbox->setSize({_view_size.x / 1.25f, _view_size.y / 1.75f});
    _hitbox->setOffset({0, _view_size.y * -0.2f});

    _gravitational_acceleration = -5;

    // start music with loop


}

void PortalRadio::update(double t, float dt) {
    // spatial audio test

    // side scrolling
    if (_position.x <= constants::world_x_min) {
        setPosition({constants::world_x_max, _position.y});
    } else if (_position.x >= constants::world_x_max) {
        setPosition({constants::world_x_min, _position.y});
    }

    _acceleration.y += _gravitational_acceleration;

    PhysicsEntity::update(t, dt);
}
