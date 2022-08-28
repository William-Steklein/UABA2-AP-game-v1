#include "JetpackBonus.h"

JetpackBonus::JetpackBonus(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize,
                           AnimationPlayer animationPlayer, AudioPlayer audioPlayer, bool isStatic)
        : Bonus(position, std::move(camera), viewSize, std::move(animationPlayer), std::move(audioPlayer), isStatic),
          _time_passed(0) {

}

void JetpackBonus::update(double t, float dt) {
    if (_active && _time_passed < constants::bonus::jetpack_duration) {
        _time_passed += dt;
        applyEffect();
    } else {
        _active = false;
    }

    Bonus::update(t, dt);
}

void JetpackBonus::applyEntity(const std::weak_ptr<PhysicsEntity> &other) {
    Bonus::applyEntity(other);

    // set affected entity velocity to 0 if negative
//    std::shared_ptr<PhysicsEntity> affected_entity = _affected_entity.lock();
//    if (affected_entity) {
//        affected_entity->setVelocity({affected_entity->getVelocity().x, 0});
////        if (affected_entity->getVelocity().y < 0) {
////            affected_entity->setVelocity({affected_entity->getVelocity().x, 0});
////        }
//    }
}

void JetpackBonus::applyEffect() {
    std::shared_ptr<PhysicsEntity> affected_entity = _affected_entity.lock();
    if (affected_entity) {
        affected_entity->addForce({0, constants::bonus::jetpack_force_amount});
//        std::cout << "adding " << constants::bonus::jetpack_force_amount << " force" << std::endl;
//        std::cout << "current force: " << affected_entity->getForce() << std::endl;
//        std::cout << "current velocity: " << affected_entity->getVelocity() << std::endl;
//        std::cout << "**********************" << std::endl;
    }
}
