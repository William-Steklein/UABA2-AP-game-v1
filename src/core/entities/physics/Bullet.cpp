#include "Bullet.h"

Bullet::Bullet(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize, bool up,
               AnimationPlayer animationPlayer, AudioPlayer audioPlayer, bool isStatic)
        : PhysicsEntity(position, std::move(camera), viewSize, std::move(animationPlayer), std::move(audioPlayer),
                        isStatic), _up(up) {
    _min_neg_velocity = {-constants::bullet::velocity, -constants::bullet::velocity};
    _max_pos_velocity = {constants::bullet::velocity, constants::bullet::velocity};

    if (_up) {
        _velocity.y = constants::bullet::velocity;
    } else {
        _velocity.y = - constants::bullet::velocity;
    }
}

void Bullet::update(double t, float dt) {
    PhysicsEntity::update(t, dt);
}
