#include "PhysicsEntity.h"

PhysicsEntity::PhysicsEntity(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize,
                             std::shared_ptr<std::map<std::string, AnimationPlayer>> animation_group, float mass,
                             bool is_static) : Entity(position, std::move(camera), viewSize,
                                                      std::move(animation_group)), _is_static(is_static), _mass(mass),
                                               _gravitational_acceleration(0) {
    _hitbox = std::make_shared<Hitbox>(_position, _view_size);

}

void PhysicsEntity::update(double t, float dt) {
    if (_is_static) {
        Entity::update(t, dt);
        return;
    }

    // force acceleration
    _acceleration += _force / _mass;

    // verlet integration t(position): position + velocity * timestep + (acceleration * timestep^2) / 2
    move(_velocity * dt + _acceleration * dt * dt / 2);
    _velocity += _acceleration * dt;

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

bool PhysicsEntity::isIsStatic() const {
    return _is_static;
}

void PhysicsEntity::setIsStatic(bool isStatic) {
    _is_static = isStatic;
}

float PhysicsEntity::getMass() const {
    return _mass;
}

void PhysicsEntity::setMass(float mass) {
    _mass = mass;
}

const Vector2f &PhysicsEntity::getForce() const {
    return _force;
}

void PhysicsEntity::setForce(const Vector2f &force) {
    _force = force;
}

const Vector2f &PhysicsEntity::getVelocity() const {
    return _velocity;
}

void PhysicsEntity::setVelocity(const Vector2f &velocity) {
    _velocity = velocity;
}

const Vector2f &PhysicsEntity::getAcceleration() const {
    return _acceleration;
}

void PhysicsEntity::setAcceleration(const Vector2f &acceleration) {
    _acceleration = acceleration;
}

void PhysicsEntity::resolveCollision(const PhysicsEntity &other) {
    Vector2f displacement = _hitbox->getDisplacementToCollision(*other._hitbox);

    if (std::abs(displacement.x) == std::abs(displacement.y)) {
        move({displacement.x, displacement.y});
        _velocity.x = 0;
    } else if (std::abs(displacement.x) < std::abs(displacement.y)) {
        move({displacement.x, 0});
        _velocity.x = 0;
    } else {
        move({0, displacement.y});
        _velocity.y = 0;
    }

    updateView();
}
