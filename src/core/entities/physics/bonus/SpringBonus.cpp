#include "SpringBonus.h"

void SpringBonus::applyEffect() {
    std::shared_ptr<PhysicsEntity> affected_entity = _affected_entity.lock();
    if (affected_entity) {
        affected_entity->addVelocity({0, constants::player::jump_velocity *
                                         constants::bonus::spring_jump_velocity_multiplier});
    }
}
