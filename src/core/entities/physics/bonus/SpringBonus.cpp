#include "SpringBonus.h"

void SpringBonus::applyEffect() {
    std::shared_ptr<PhysicsEntity> affected_entity = _affected_entity.lock();
    if (_active && affected_entity) {
        affected_entity->setVelocity({0, (2 * (constants::player::jump_height * 5) / constants::player::jump_dt)});
    }
    _active = false;
}
