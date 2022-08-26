#ifndef GAMEENGINE_SPRINGBONUS_H
#define GAMEENGINE_SPRINGBONUS_H


#include "Bonus.h"
#include "../../../constants/constants.h"

class SpringBonus : public Bonus {
public:
    using Bonus::Bonus;

    void applyEffect() override;
};


#endif //GAMEENGINE_SPRINGBONUS_H
