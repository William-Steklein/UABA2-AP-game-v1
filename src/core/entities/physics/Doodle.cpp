#include "Doodle.h"

#include <utility>

Doodle::Doodle(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize,
               std::shared_ptr<InputMap> input_map, AnimationPlayer animation_player, AudioPlayer audio_player,
               bool is_static)
        : PhysicsEntity(position, std::move(camera), viewSize, std::move(animation_player), std::move(audio_player),
                        is_static), _input_map(std::move(input_map)) {
    _hitbox->setSize({_view_size.x / 3.75f, _view_size.y / 1.25f});
    _hitbox->setOffset({0, -0.072f * _view_size.y});

    // standing rays
    Vector2f r1(_hitbox->getPosition().x - _hitbox->getSize().x / 2.1f,
                _hitbox->getPosition().y - _hitbox->getSize().y / 2);
    Vector2f r2(_hitbox->getPosition().x + _hitbox->getSize().x / 2.1f, r1.y);
    float ray_length = 0.05;

    _rays.push_back(std::make_shared<Ray>(Ray(r1, {r1.x, r1.y - ray_length})));
    _rays.push_back(std::make_shared<Ray>(Ray(r2, {r2.x, r2.y - ray_length})));

    // movement / jump physics
    float jump_dt = 0.6;
    float jump_height = 1;

    _mass = 20;
    _initial_jump_velocity = 2 * jump_height / jump_dt;
    _horizontal_movement_force = 200;

    setupPlayerPhysics(jump_dt, jump_height);

    playAnimation("idle");
}

void Doodle::update(double t, float dt) {
    playerController(dt);
//    testController();



    applySideScrolling();

    PhysicsEntity::update(t, dt);
}

void Doodle::reset() {
    setPosition({0, 2.5f});

    _velocity.clear();

    for (const auto &standing_ray: _rays) {
        standing_ray->reset();
    }
}

void Doodle::playerController(float dt) {
    _standing = false;

    std::string curr_anim = _animation_player.getCurrentAnimationName();

    // reset player
    if (_input_map->r) {
        reset();
    }

    // check if standing
    for (const auto &standing_ray: _rays) {
        if (standing_ray->isCollided()) {
            _standing = true;
            standing_ray->reset();
        }
    }

    if (_standing && curr_anim != "crouch" && curr_anim != "run") {
        playAnimation("idle");
    }

    if (_standing && _input_map->s && curr_anim != "run") {
        playAnimation("crouch");
    }

    if ((curr_anim == "crouch" && !_input_map->s) || (curr_anim == "run" && !(_input_map->d || _input_map->a))) {
        playAnimation("idle");
    }

    // jumping
    if (_standing && _input_map->w) {
        _velocity.y = _initial_jump_velocity;
        _standing = false;

        playAnimation("jump");
        playSound("scream", true, false);
    }

    // falling
    if (!_standing && _velocity.y < 0 && curr_anim != "fall") {
        playAnimation("fall");
    }

    // left / right movement
    if (_input_map->d) {
        _animation_player.setHorizontalMirror(false);

        if (curr_anim != "crouch") _force.x += _horizontal_movement_force;

        if (_standing && curr_anim != "crouch") {
            playAnimation("run");
        }
    }
    if (_input_map->a) {
        _animation_player.setHorizontalMirror(true);

        if (curr_anim != "crouch") _force.x -= _horizontal_movement_force;

        if (_standing && curr_anim != "crouch") {
            playAnimation("run");
        }
    }

    // gravity
    if (!_standing) {
        applyGravity();
    }

    applyFriction();
    applyDrag();
}

void Doodle::testController() {
    float movement_force = 15.f;

    // reset player
    if (_input_map->r) {
        reset();
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

    applyFriction();
    applyDrag();
}
