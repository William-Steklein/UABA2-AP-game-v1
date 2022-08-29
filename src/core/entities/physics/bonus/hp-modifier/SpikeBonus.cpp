#include "SpikeBonus.h"

SpikeBonus::SpikeBonus(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize,
                       AnimationPlayer animationPlayer, AudioPlayer audioPlayer, bool isStatic)
        : Bonus(position, std::move(camera), viewSize, std::move(animationPlayer), std::move(audioPlayer), isStatic),
          _damage(1) {
    _passthrough = true;
}

void SpikeBonus::update(double t, float dt) {
    Bonus::update(t, dt);
}

void SpikeBonus::applyEffect() {
    std::shared_ptr<PhysicsEntity> affected_entity = _affected_entity.lock();
    if (_active && affected_entity) {
        affected_entity->subtractHitPoints(_damage);
    }
    _active = false;
}
