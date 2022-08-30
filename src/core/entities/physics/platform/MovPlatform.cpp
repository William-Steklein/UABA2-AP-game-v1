#include "MovPlatform.h"

MovPlatform::MovPlatform(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize,
                         bool horizontal, AnimationPlayer animationPlayer, AudioPlayer audioPlayer, bool isStatic)
        : Platform(position, std::move(camera), viewSize, std::move(animationPlayer), std::move(audioPlayer),
                   isStatic), _horizontal(horizontal), _going_left(Random::get_instance().uniform_int(0, 1)) {
    if (_horizontal) {
        _bounderies = {constants::camera_view_x_min + _hitbox->getSize().x / 2,
                       constants::camera_view_x_max - _hitbox->getSize().x / 2};
    } else {
        // todo: constant
        float y_boundery_scale = 0.3f;

        _bounderies = {_position.y -
                       ((constants::camera_view_y_max - constants::camera_view_y_min) / 2) * y_boundery_scale,
                       _position.y +
                       ((constants::camera_view_y_max - constants::camera_view_y_min) / 2) * y_boundery_scale};
    }
}

void MovPlatform::update(double t, float dt) {
    // todo: constant
    float movement_amount = 0.01;

    if (_horizontal) {
        if (_going_left) {
            move({-movement_amount, 0});
        } else {
            move({movement_amount, 0});
        }

        if (_position.x < _bounderies.x) {
            _going_left = false;
        } else if (_position.x > _bounderies.y) {
            _going_left = true;
        }
    } else {
        if (_going_left) {
            move({0, -movement_amount});
        } else {
            move({0, movement_amount});
        }

        if (_position.y < _bounderies.x) {
            _going_left = false;
        } else if (_position.y > _bounderies.y) {
            _going_left = true;
        }
    }

    PhysicsEntity::update(t, dt);
}
