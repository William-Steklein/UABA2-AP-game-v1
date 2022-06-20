#ifndef GAMEENGINE_IENTITYVIEWCREATOR_H
#define GAMEENGINE_IENTITYVIEWCREATOR_H


#include <memory>
#include <vector>
#include "Entity.h"
#include "../animation/AnimationStateMachine.h"

class IEntityViewCreator {
public:
    virtual void createEntityView(std::shared_ptr<Entity> entity, std::vector<std::string> texture_files,
                                  AnimationStateMachine animation_state_machine, uint layer) = 0;
};


#endif //GAMEENGINE_IENTITYVIEWCREATOR_H
