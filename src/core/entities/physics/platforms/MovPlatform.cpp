#include "MovPlatform.h"

MovPlatform::MovPlatform(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize,
                         AnimationPlayer animationPlayer, AudioPlayer audioPlayer, bool isStatic)
        : Platform(position, std::move(camera), viewSize, std::move(animationPlayer), std::move(audioPlayer),
                   isStatic), _horizontal(true), _going_left(true), _vertical_pivot(_position.y) {

}

void MovPlatform::update(double t, float dt) {
    float boundery_scale = 0.8f;
    float movement_amount = 0.01;

    if (_horizontal) {
        Vector2f bounderies = Vector2f(constants::camera_view_x_min, constants::camera_view_x_max) * boundery_scale;

        if (_going_left) {
            move({-movement_amount, 0});
        } else {
            move({movement_amount, 0});
        }

        if (_position.x < bounderies.x) {
            _going_left = false;
        } else if (_position.x > bounderies.y) {
            _going_left = true;
        }
    } else {
        Vector2f bounderies =
                Vector2f(_vertical_pivot - (constants::camera_view_y_max - constants::camera_view_y_min) / 2,
                         _vertical_pivot + (constants::camera_view_y_max - constants::camera_view_y_min) / 2) *
                boundery_scale;

        if (_going_left) {
            move({0, -movement_amount});
        } else {
            move({0, movement_amount});
        }

        if (_position.y < bounderies.x) {
            _going_left = false;
        } else if (_position.y > bounderies.y) {
            _going_left = true;
        }
    }

    PhysicsEntity::update(t, dt);
}
