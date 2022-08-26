#ifndef GAMEENGINE_JETPACKBONUS_H
#define GAMEENGINE_JETPACKBONUS_H


#include "Bonus.h"

class JetpackBonus : public Bonus {
private:

public:
    using Bonus::Bonus;

    void applyBonus(const std::shared_ptr<PhysicsEntity> &other) override;
};


#endif //GAMEENGINE_JETPACKBONUS_H
