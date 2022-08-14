#include "PhysicsEntity.h"

PhysicsEntity::PhysicsEntity(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize,
                             std::shared_ptr<std::map<std::string, Animation>> animation_group, float mass,
                             bool is_static) : Entity(position, std::move(camera), viewSize,
                                                      std::move(animation_group)), _is_static(is_static),
                                               _previous_hitbox_position(_position), _mass(mass) {
    _hitbox = std::make_shared<Hitbox>(_position, _view_size);

}

void PhysicsEntity::update(double t, float dt) {
    // store old pos and vel for collision resolution
    _previous_hitbox_position = _hitbox->getPosition();
    _previous_velocity = _velocity;

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

const Vector2f &PhysicsEntity::getPreviousPosition() const {
    return _previous_hitbox_position;
}

const Vector2f &PhysicsEntity::getPreviousVelocity() const {
    return _previous_velocity;
}

void PhysicsEntity::resolveCollision(const PhysicsEntity &other) {
    // case 1: other is static
    Vector2f displacement = Hitbox(_previous_hitbox_position, _hitbox->getSize()).getDisplacementToCollision(
            {other._previous_hitbox_position, other._hitbox->getSize()});

    Vector2f collision_time = {_previous_velocity.x != 0 ? std::abs(displacement.x / _previous_velocity.x) : 0,
                               _previous_velocity.y != 0 ? std::abs(displacement.y / _previous_velocity.y) : 0};

    Vector2f move_vector;

    if (_previous_velocity.x != 0 && _previous_velocity.y == 0) {
        move_vector.x = _previous_velocity.x * collision_time.x;
    } else if (_previous_velocity.x == 0 && _previous_velocity.y != 0) {
        move_vector.y = _previous_velocity.y * collision_time.y;
    } else {
//        move_vector = _previous_velocity * std::min(collision_time.x, collision_time.y);
        if (collision_time.x < collision_time.y) {
            move_vector.x = _previous_velocity.x * collision_time.x;
        } else {
            move_vector.y = _previous_velocity.y * collision_time.y;
        }
    }

    std::cout << _previous_velocity << std::endl;
    std::cout << -1 * (move_vector) << std::endl;
    std::cout << "********************" << std::endl;

    setPosition(_previous_hitbox_position - _hitbox_offset - move_vector * 1.001);
    updateView();

    // case 2: this is static

    // case 3: both are dynamic
}
