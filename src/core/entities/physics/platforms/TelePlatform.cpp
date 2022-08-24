#include "TelePlatform.h"

TelePlatform::TelePlatform(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize,
                           AnimationPlayer animationPlayer, AudioPlayer audioPlayer, bool isStatic)
        : Platform(position, std::move(camera), viewSize, std::move(animationPlayer), std::move(audioPlayer),
                   isStatic), _horizontal(false), _left(true), _vertical_pivot(_position.y) {
    if (_horizontal) {
        _position.x = constants::camera_view_x_min * 0.6f;
    } else {
        _position.y =
                (_vertical_pivot - (constants::camera_view_y_max - constants::camera_view_y_min) / 2) * (0.6f / 2);
    }
}

void TelePlatform::update(double t, float dt) {
    float boundery_scale = 0.6f;

    if (_horizontal) {
        Vector2f bounderies = Vector2f(constants::camera_view_x_min, constants::camera_view_x_max) * boundery_scale;

        if (_collided) {
            _collided = false;
            if (_left) {
                // go right
                setPosition({bounderies.y, _position.y});
            } else {
                setPosition({bounderies.x, _position.y});
            }
            _left = !_left;
        }

    } else {
        Vector2f bounderies =
                Vector2f(_vertical_pivot - (constants::camera_view_y_max - constants::camera_view_y_min) / 2,
                         _vertical_pivot + (constants::camera_view_y_max - constants::camera_view_y_min) / 2) *
                boundery_scale / 2;

        if (_collided) {
            _collided = false;
            if (_left) {
                // go right
                setPosition({_position.x, bounderies.y});
            } else {
                setPosition({_position.x, bounderies.x});
            }
            _left = !_left;
        }
    }

    PhysicsEntity::update(t, dt);
}
