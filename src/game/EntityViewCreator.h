#ifndef GAMEENGINE_ENTITYVIEWCREATOR_H
#define GAMEENGINE_ENTITYVIEWCREATOR_H

#include <map>
#include "core/entities/IEntityViewCreator.h"
#include "EntityView.h"

class EntityViewCreator : public IEntityViewCreator {
private:
    std::map<unsigned int, std::vector<std::weak_ptr<EntityView>>> _entity_views;

public:
    void createEntityView(std::shared_ptr<Entity> entity, std::vector<std::string> texture_files,
                          AnimationStateMachine animation_state_machine, unsigned int layer) override;

    std::vector<std::shared_ptr<EntityView>> getEntityViews();
};


#endif //GAMEENGINE_ENTITYVIEWCREATOR_H
