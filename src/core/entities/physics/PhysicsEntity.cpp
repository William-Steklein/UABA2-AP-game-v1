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

    // position(t): position + velocity * timestep + (acceleration / 2 * timestep^2)
    move(_velocity * dt + _acceleration / 2 * dt * dt);
    // verlet integration
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

void PhysicsEntity::resolveCollision(PhysicsEntity &other) {


    Vector2f displacement = _hitbox->getDisplacementToCollision(*other._hitbox);
    Vector2f move_vector;

    Vector2f new_velocity_this = _velocity;
    Vector2f new_velocity_other = other._velocity;

    if (std::abs(displacement.x) == std::abs(displacement.y)) {
        move_vector = {displacement.x, displacement.y};
    } else if (std::abs(displacement.x) < std::abs(displacement.y)) {
        move_vector = {displacement.x, 0};

        new_velocity_this.x = 0;
        new_velocity_other.x = 0;
    } else {
        move_vector = {0, displacement.y};

        new_velocity_this.y = 0;
        new_velocity_other.y = 0;
    }

    if (!_is_static && other._is_static) {
        // this is dynamic
        move(move_vector);
        _velocity = new_velocity_this;

        updateView();

    } else if (_is_static && !other._is_static) {
        // other is dynamic
        other.move(move_vector * -1);
        other._velocity = new_velocity_other;

        other.updateView();

    } else if (!_is_static && !other._is_static) {
        // if both are dynamic
        float alpha = other._mass / _mass;

        move(lerp({0, 0}, move_vector, alpha));
        other.move(lerp({0, 0}, move_vector * -1, 1 - alpha));

        _velocity = new_velocity_this;
        other._velocity = new_velocity_other;

        updateView();
        other.updateView();
    }


}
