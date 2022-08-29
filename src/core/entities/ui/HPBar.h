#ifndef GAMEENGINE_HPBAR_H
#define GAMEENGINE_HPBAR_H


#include "../physics/PhysicsEntity.h"

class HPBar {
private:
    bool _acitve;

public:
    HPBar(const std::weak_ptr<PhysicsEntity> &entity);
};


#endif //GAMEENGINE_HPBAR_H
