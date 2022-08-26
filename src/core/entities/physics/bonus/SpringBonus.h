#ifndef GAMEENGINE_SPRINGBONUS_H
#define GAMEENGINE_SPRINGBONUS_H


#include "Bonus.h"
#include "../../../constants/constants.h"

class SpringBonus : public Bonus {
private:

public:
    using Bonus::Bonus;

    void applyBonus(const std::shared_ptr<PhysicsEntity> &other) override;
};


#endif //GAMEENGINE_SPRINGBONUS_H
