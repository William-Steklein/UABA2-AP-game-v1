#include "PhysicsEntity.h"

PhysicsEntity::PhysicsEntity(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize,
                             std::shared_ptr<std::map<std::string, Animation>> animation_group, float mass,
                             bool is_static)
        : Entity(position, std::move(camera), viewSize, std::move(animation_group)), _mass(mass),
          _is_static(is_static) {
    _hitbox = std::make_shared<Hitbox>(_position, _view_size);
}

void PhysicsEntity::update(double t, float dt) {
    if (_is_static) {
        Entity::update(t, dt);
        return;
    }

    // force acceleration
    _acceleration += _force / _mass;

    // position: position + timestep * (velocity + timestep * acceleration / 2)
    Vector2f move_velocity = _velocity + dt * _acceleration / 2;
    move(dt * move_velocity);

    _velocity += dt * _acceleration;

    // todo: make min_value a constant
    float min_value = 1.e-4f;
    // remove small velocities
    if (_velocity.x < min_value && _velocity.x > -min_value)
        _velocity.x = 0;
    if (_velocity.y < min_value && _velocity.y > -min_value)
        _velocity.y = 0;

    // clear forces/accelerations
    _force = {0, 0};
    _acceleration = {0, 0};

    Entity::update(t, dt);
}
