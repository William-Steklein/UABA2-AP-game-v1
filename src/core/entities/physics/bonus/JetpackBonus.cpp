#include "JetpackBonus.h"

JetpackBonus::JetpackBonus(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize,
                           AnimationPlayer animationPlayer, AudioPlayer audioPlayer, bool isStatic)
        : Bonus(position, std::move(camera), viewSize, std::move(animationPlayer), std::move(audioPlayer), isStatic),
          _time_passed(0) {

}

void JetpackBonus::applyEffect() {
    std::shared_ptr<PhysicsEntity> affected_entity = _affected_entity.lock();
    if (affected_entity) {
        affected_entity->addForce({0, constants::bonus::jetpack_force_amount});
    }
}

void JetpackBonus::update(double t, float dt) {
    if (_time_passed < constants::bonus::jetpack_duration) {
        _time_passed += dt;
        applyEffect();
    }

    Bonus::update(t, dt);
}
