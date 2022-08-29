#include "TelePlatform.h"

TelePlatform::TelePlatform(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize,
                           bool horizontal, AnimationPlayer animationPlayer, AudioPlayer audioPlayer, bool isStatic)
        : Platform(position, std::move(camera), viewSize, std::move(animationPlayer), std::move(audioPlayer),
                   isStatic), _horizontal(horizontal) {
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

void TelePlatform::update(double t, float dt) {
    // todo: constant
    float min_tele_distance = 0.3f;

    if (_horizontal) {
        if (_collided) {
            _collided = false;

            float new_position = Random::get_instance().uniform_real(_bounderies.x, _bounderies.y);
            float distance = std::abs(new_position - _position.x);

            if (distance < min_tele_distance) {
                if (_position.x < (_bounderies.y - _bounderies.x) / 2) {
                    new_position = _position.x + min_tele_distance;
                } else {
                    new_position = _position.x - min_tele_distance;
                }
            }

            setPosition({new_position, _position.y});
        }

    } else {
        if (_collided) {
            _collided = false;

            float new_position = Random::get_instance().uniform_real(_bounderies.x, _bounderies.y);
            float distance = std::abs(new_position - _position.y);

            if (distance < min_tele_distance) {
                if (_position.y < (_bounderies.y - _bounderies.x) / 2) {
                    new_position = _position.y + min_tele_distance;
                } else {
                    new_position = _position.y - min_tele_distance;
                }
            }

            setPosition({_position.x, new_position});
        }
    }

    PhysicsEntity::update(t, dt);
}
