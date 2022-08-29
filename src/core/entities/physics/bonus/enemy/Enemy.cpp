#include "Enemy.h"

Enemy::Enemy(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize,
             AnimationPlayer animationPlayer, AudioPlayer audioPlayer, bool isStatic)
        : SpikeBonus(position, std::move(camera), viewSize, std::move(animationPlayer), std::move(audioPlayer),
                        isStatic), _can_damage(true), _damage_delay_time_passed(0), _shoot_back(false) {
    _passthrough = false;
    // todo: constants
    _max_hit_points = 1;
    _current_hit_points = 1;
}

void Enemy::update(double t, float dt) {
    if (_current_hit_points == 0) {
        disappear();
    }

    if (!_can_damage) {
        _damage_delay_time_passed += dt;
    }

    if (_damage_delay_time_passed > constants::bonus::enemy::can_damage_duration) {
        _damage_delay_time_passed = 0;
        _can_damage = true;
    }

    PhysicsEntity::update(t, dt);
}

void Enemy::applyEffect() {
    if (_can_damage) {
        _can_damage = false;

        SpikeBonus::applyEffect();
    }

    _active = false;
}

bool Enemy::isShootBack() const {
    return _shoot_back;
}
