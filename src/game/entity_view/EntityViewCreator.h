#ifndef GAMEENGINE_ENTITYVIEWCREATOR_H
#define GAMEENGINE_ENTITYVIEWCREATOR_H

#include <map>
#include "core/entities/IEntityViewCreator.h"
#include "EntityView.h"
#include "EntitySpriteView.h"
#include "EntityTextView.h"

class EntityViewCreator : public IEntityViewCreator {
private:
    std::map<unsigned int, std::vector<std::weak_ptr<EntitySpriteView>>> _entity_sprite_views;
    std::vector<std::weak_ptr<EntityTextView>> _entity_text_views;

public:
    void createEntitySpriteView(std::shared_ptr<Entity> entity, std::vector<std::string> texture_files,
                                AnimationStateMachine animation_state_machine, unsigned int layer) override;

    void createEntityTextView(std::shared_ptr<Entity> entity) override;

    std::vector<std::shared_ptr<EntitySpriteView>> getEntitySpriteViews();

    std::vector<std::shared_ptr<EntityTextView>> getEntityTextViews();
};


#endif //GAMEENGINE_ENTITYVIEWCREATOR_H
