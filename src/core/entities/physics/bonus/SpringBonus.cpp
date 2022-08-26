#include "SpringBonus.h"

void SpringBonus::applyBonus(const std::shared_ptr<PhysicsEntity> &other) {
    // todo: spring jump velocity multiplier constant
    other->addVelocity({0, (2 * constants::player::jump_height / constants::player::jump_dt) * 5});
}