#ifndef GAMEENGINE_ENTITYVIEWCREATOR_H
#define GAMEENGINE_ENTITYVIEWCREATOR_H

#include <map>
#include "core/entities/IEntityViewCreator.h"
#include "EntityView.h"
#include "EntitySpriteView.h"
#include "EntityTextView.h"

class EntityViewCreator : public IEntityViewCreator {
private:
    std::map<std::string, std::shared_ptr<std::vector<sf::Texture>>> _texture_groups;

    std::map<unsigned int, std::vector<std::weak_ptr<EntitySpriteView>>> _entity_sprite_views;
    std::vector<std::weak_ptr<EntityTextView>> _entity_text_views;

public:
    void loadTextureGroup(const std::string &texture_group_name,
                          const std::vector<std::string> &texture_filenames) override;

    void createEntitySpriteView(std::shared_ptr<Entity> entity, unsigned int layer) override;

    void createEntityTextView(std::shared_ptr<Entity> entity) override;

    std::vector<std::shared_ptr<EntitySpriteView>> getEntitySpriteViews();

    std::vector<std::shared_ptr<EntityTextView>> getEntityTextViews();
};


#endif //GAMEENGINE_ENTITYVIEWCREATOR_H
