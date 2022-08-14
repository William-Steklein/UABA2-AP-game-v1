#include "Doodle.h"

Doodle::Doodle(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize,
               std::shared_ptr<std::map<std::string, Animation>> animation_group,
               const std::shared_ptr<InputMap> &input_map, float mass, bool is_static)
        : PhysicsEntity(position, std::move(camera), viewSize, std::move(animation_group), mass, is_static), _prev_t(0),
          _facing_left(true), _current_animation(1), _input_map(input_map) {
    _hitbox->setSize({_view_size.x / 3.f, _view_size.y / 1.25f});
    setHitboxOffset({0, -0.072f * _view_size.y});

    float jump_dt = 0.6;
    float jump_height = 1;

    _gravitational_acceleration = -2 * jump_height / (jump_dt * jump_dt);
    _initial_jump_velocity = 2 * jump_height / jump_dt;

    _horizontal_movement_force = 200;
    _drag = 0.015;
    _friction = 0.3;

    _mass = 20;
    _max_velocity = {1.4, _initial_jump_velocity * 1.5f};

    startAnimation("idle", _facing_left);
//    startAnimation("crouch", _facing_left);
}

void Doodle::update(double t, float dt) {
    float wait_duration = 3;

//    if (t - _prev_t >= (wait_duration)) {
//        _prev_t = t;
//
//        switch (_current_animation) {
//            case 0:
//                startAnimation("crouch", _facing_left);
//                break;
//            case 1:
//                startAnimation("fall", _facing_left);
//                break;
//            case 2:
//                startAnimation("idle", _facing_left);
//                break;
//            case 3:
//                startAnimation("jump", _facing_left);
//                break;
//            case 4:
//                startAnimation("run", _facing_left);
//                _current_animation = -1;
//                break;
//            default:
//                _current_animation = -1;
//                break;
//        }
//        _current_animation++;
//    }

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

    // crouching
    if (_input_map->c) {
        if (_current_animation_name != "crouch") {
            startAnimation("crouch", _facing_left);
        }
    } else if (_current_animation_name != "idle") {
        startAnimation("idle", _facing_left);
    }

    // ground collision
    if (_hitbox->getPosition().y - (_hitbox->getSize().y / 2) < 0) {
        setPosition({_position.x, _hitbox->getSize().y / 2 - _hitbox_offset.y});
        _standing = true;
        _velocity.y = 0;
    }

    // gravity
    if (!_standing) {
        _acceleration.y += _gravitational_acceleration;
    }

    // friction & drag
//    Vector2f friction_force = _velocity * _friction;
//    if (_velocity.length() < 0.1) {
//        friction_force *= 3;
//    }
//    Vector2f drag_force = _velocity * _velocity.length() * _drag;
//    _acceleration -= friction_force + drag_force;

    // side scrolling
    if (_position.x <= constants::world_x_min) {
        setPosition({constants::world_x_max, _position.y});
    } else if (_position.x >= constants::world_x_max) {
        setPosition({constants::world_x_min, _position.y});
    }

    PhysicsEntity::update(t, dt);
}
