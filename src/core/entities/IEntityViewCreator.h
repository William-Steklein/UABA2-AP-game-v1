#ifndef GAMEENGINE_IENTITYVIEWCREATOR_H
#define GAMEENGINE_IENTITYVIEWCREATOR_H


#include <memory>
#include <vector>
#include "Entity.h"
#include "../animation/AnimationStateMachine.h"

class IEntityViewCreator {
public:
    virtual void createEntitySpriteView(std::shared_ptr<Entity> entity, std::vector<std::string> texture_files,
                                        AnimationStateMachine animation_state_machine, unsigned int layer) = 0;

    virtual void createEntityTextView(std::shared_ptr<Entity> entity) = 0;
};


#endif //GAMEENGINE_IENTITYVIEWCREATOR_H
