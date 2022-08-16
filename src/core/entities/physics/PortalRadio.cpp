#include "PortalRadio.h"

#include <utility>

PortalRadio::PortalRadio(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize,
                         std::shared_ptr<std::map<std::string, AnimationPlayer>> animationGroup, float mass,
                         bool isStatic) : PhysicsEntity(position, std::move(camera), viewSize,
                                                        std::move(animationGroup), mass, isStatic) {
    _hitbox->setSize({_view_size.x / 1.25f, _view_size.y / 1.75f});
    setHitboxOffset({0, _view_size.y * -0.2f});

    _gravitational_acceleration = -5;

    // start music with loop


}

void PortalRadio::update(double t, float dt) {
    // spatial audio test

    _acceleration.y += _gravitational_acceleration;

    // ground collision
    if (_hitbox->getPosition().y - (_hitbox->getSize().y / 2) < 0) {
        setPosition({_position.x, _hitbox->getSize().y / 2 - _hitbox_offset.y});
        _velocity.y = 0;
    }

    PhysicsEntity::update(t, dt);
}
