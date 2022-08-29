#include "Enemy.h"

Enemy::Enemy(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize,
             AnimationPlayer animationPlayer, AudioPlayer audioPlayer, bool isStatic)
        : PhysicsEntity(position, std::move(camera), viewSize, std::move(animationPlayer), std::move(audioPlayer),
                        isStatic) {
    _max_hit_points = 1;
    _current_hit_points = 1;
}

void Enemy::update(double t, float dt) {
    if (_current_hit_points == 0) {
        disappear();
    }

    PhysicsEntity::update(t, dt);
}

