#include "HPBonus.h"

HPBonus::HPBonus(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize,
                       AnimationPlayer animationPlayer, AudioPlayer audioPlayer, bool isStatic)
        : Bonus(position, std::move(camera), viewSize, std::move(animationPlayer), std::move(audioPlayer), isStatic),
          _hp_addition(1) {
    playAnimation("red");
}

void HPBonus::update(double t, float dt) {
    Bonus::update(t, dt);
}

void HPBonus::applyEffect() {
    std::shared_ptr<PhysicsEntity> affected_entity = _affected_entity.lock();
    if (_active && affected_entity) {
        affected_entity->addHitPoints(_hp_addition);
    }
    _active = false;
    // todo: constants
    notifyObservers(200, 25);
}
