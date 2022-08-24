#include "PhysicsEntity.h"

PhysicsEntity::PhysicsEntity(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize,
                             AnimationPlayer animation_player, AudioPlayer audio_player, bool is_static) :
        Entity(position, std::move(camera), viewSize, std::move(animation_player), std::move(audio_player)),
        _is_static(is_static), _mass(1), _gravitational_acceleration({0, 0}), _passthrough(false), _collided(false) {
    _hitbox = std::make_shared<Hitbox>(_position, _view_size);

}

void PhysicsEntity::setupPlayerPhysics(float jump_dt, float jump_height) {
    _gravitational_acceleration = {0, -2 * jump_height / (jump_dt * jump_dt)};
    _max_velocity = {1.5f, 2 * jump_height / jump_dt * 1.5f};
    _drag = {0.15f, 0};
    _friction = {5.f, 0};
}

void PhysicsEntity::update(double t, float dt) {
    if (_is_static) {
        Entity::update(t, dt);
        return;
    }
    // max velocity
    _velocity = {std::clamp(_velocity.x, -_max_velocity.x, _max_velocity.x),
                 std::clamp(_velocity.y, -_max_velocity.y, _max_velocity.y)};

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

void PhysicsEntity::applyGravity() {
    _acceleration += _gravitational_acceleration;
}

void PhysicsEntity::applyFriction() {
    Vector2f friction_force = {_velocity.x * _friction.x, _velocity.y * _friction.y};
    if (_velocity.length() < 0.1) {
        friction_force *= 3;
    }
    _acceleration -= friction_force;
}

void PhysicsEntity::applyDrag() {
    Vector2f drag_force = _velocity.x * _velocity.x * _drag;
    _acceleration -= drag_force;
}

bool PhysicsEntity::isPassthrough() const {
    return _passthrough;
}

void PhysicsEntity::setPassthrough(bool passthrough) {
    _passthrough = passthrough;
}

void PhysicsEntity::applySideScrolling() {
    if (_position.x <= constants::world_x_min) {
        setPosition({constants::world_x_max, _position.y});
    } else if (_position.x >= constants::world_x_max) {
        setPosition({constants::world_x_min, _position.y});
    }
}

void PhysicsEntity::resolveCollision(PhysicsEntity &other) {
    Vector2f displacement = _hitbox->getDisplacementToCollision(*other._hitbox);
    Vector2f move_vector;

    Vector2f new_velocity_this = _velocity;
    Vector2f new_velocity_other = other._velocity;

    if (other._passthrough) {

        if (_velocity.y < 0 && displacement.y > 0) {
            move_vector.y = displacement.y;
            move(move_vector);
            _velocity.y = 0;

            updateView();
            _collided = true;
            other._collided = true;
        }

        return;
    }

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
        // both are dynamic
        float alpha;

        if (other._mass < _mass) {
            alpha = other._mass / _mass;
        } else {
            alpha = 1 - (_mass / other._mass);
        }

        move(lerp({0, 0}, move_vector, alpha));
        other.move(lerp({0, 0}, move_vector * -1, 1 - alpha));

        Vector2f new_velocity;

        if (_velocity.length() + other._velocity.length() < (_velocity + other._velocity).length()) {
            new_velocity = _velocity + other._velocity;
        } else {
            new_velocity = _velocity.length() > other._velocity.length() ? _velocity : other._velocity;
        }

        _velocity = new_velocity;
        other._velocity = new_velocity;

        updateView();
        other.updateView();
    }

    _collided = true;
    other._collided = true;
}

void PhysicsEntity::setCollided() {
    _collided = true;
}
