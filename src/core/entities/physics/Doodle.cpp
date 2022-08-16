#include "Doodle.h"

#include <utility>

Doodle::Doodle(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize,
               std::shared_ptr<std::map<std::string, AnimationPlayer>> animation_group,
               std::shared_ptr<InputMap> input_map, float mass, bool is_static)
        : PhysicsEntity(position, std::move(camera), viewSize, std::move(animation_group), mass, is_static),
          _input_map(std::move(input_map)) {
    _hitbox->setSize({_view_size.x / 3.f, _view_size.y / 1.25f});
    _hitbox->setOffset({0, -0.072f * _view_size.y});

    float jump_dt = 0.6;
    float jump_height = 1;

    _gravitational_acceleration = -2 * jump_height / (jump_dt * jump_dt);
    _initial_jump_velocity = 2 * jump_height / jump_dt;

    _horizontal_movement_force = 200;
    _drag = 0.015;
    _friction = 0.7;

    _mass = 20;
    _max_velocity = {1.4, _initial_jump_velocity * 1.5f};

    startAnimation("idle");
}

void Doodle::update(double t, float dt) {
    adventurerController();
//    testController();
//    testController2();

    // side scrolling
    if (_position.x <= constants::world_x_min) {
        setPosition({constants::world_x_max, _position.y});
    } else if (_position.x >= constants::world_x_max) {
        setPosition({constants::world_x_min, _position.y});
    }

    PhysicsEntity::update(t, dt);
}

void Doodle::testController() {
    _velocity.clear();

    float movement_speed = 0.01f;

    // player controller
    if (_input_map->a) {
        move({-movement_speed, 0});
        _velocity += {-movement_speed, 0};
    }
    if (_input_map->d) {
        move({movement_speed, 0});
        _velocity += {movement_speed, 0};
    }
    if (_input_map->w) {
        move({0, movement_speed});
        _velocity += {0, movement_speed};
    }
    if (_input_map->s) {
        move({0, -movement_speed});
        _velocity += {0, -movement_speed};
    }
}

void Doodle::testController2() {
    float movement_force = 15.f;

    // reset player
    if (_input_map->r) {
        setPosition({0, 2.5f});
        setVelocity({0, 0});
        _standing = false;
    }

    // player controller
    if (_input_map->a) {
        _force += {-movement_force, 0};
    }
    if (_input_map->d) {
        _force += {movement_force, 0};
    }
    if (_input_map->w) {
        _force += {0, movement_force};
    }
    if (_input_map->s) {
        _force += {0, -movement_force};
    }

    // friction & drag
    Vector2f friction_force = _velocity * _friction;
    if (_velocity.length() < 0.1) {
        friction_force *= 3;
    }
    Vector2f drag_force = _velocity * _velocity.length() * _drag;
    _acceleration -= friction_force + drag_force;
}

void Doodle::adventurerController() {
    // reset player
    if (_input_map->r) {
        setPosition({0, 1});
        _standing = false;
    }

    // jumping
    if (_standing && _input_map->w) {
        _velocity.y = _initial_jump_velocity;
        _standing = false;
        startAnimation("jump");
    }

    // crouching
    if (_input_map->s) {
        if (_current_animation_name != "crouch") {
            startAnimation("crouch", _h_mirror);
        }
    } else if (_current_animation_name != "idle" && (_current_animation_name != "jump" || _standing)) {
        startAnimation("idle", _h_mirror);
    }

    // ground collision
    if (_hitbox->getPosition().y - (_hitbox->getSize().y / 2) < 0) {
        setPosition({_position.x, _hitbox->getSize().y / 2 - _hitbox->getOffset().y});
        _standing = true;
        _velocity.y = 0;
    }

    // left / right movement
    if (_input_map->d) {
        _force.x += _horizontal_movement_force;
        _h_mirror = false;
    }
    if (_input_map->a) {
        _force.x -= _horizontal_movement_force;
        _h_mirror = true;
    }

    // gravity
    if (!_standing) {
        _acceleration.y += _gravitational_acceleration;
    }

    // friction & drag
    Vector2f friction_force = _velocity * _friction;
    if (_velocity.length() < 0.1) {
        friction_force *= 3;
    }
    Vector2f drag_force = _velocity * _velocity.length() * _drag;
    _acceleration -= friction_force + drag_force;
}
