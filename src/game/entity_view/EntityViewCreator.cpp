#include "EntityViewCreator.h"

void EntityViewCreator::loadTextureGroup(const std::string &texture_group_name,
                                         const std::vector<std::string> &texture_filenames) {
    std::shared_ptr<std::vector<sf::Texture>> texture_group = std::make_shared<std::vector<sf::Texture>>();

    for (const auto &texture_filename: texture_filenames) {
        sf::Texture new_texture;

        if (!new_texture.loadFromFile(texture_filename)) {
            std::cerr << "Couldn't load the texture \"" + texture_filename + "\"" << std::endl;
        }

        texture_group->push_back(new_texture);
    }

    _texture_groups[texture_group_name] = texture_group;
}

void EntityViewCreator::createEntitySpriteView(std::shared_ptr<Entity> entity, unsigned int layer) {
    // todo: assert / exception if no texturegroupname than the entity has not corresponding texture files

    std::shared_ptr<EntitySpriteView> new_entity_sprite_view(
            new EntitySpriteView(entity, _texture_groups[entity->getTextureGroupName()]));
    std::weak_ptr<EntitySpriteView> new_entity_sprite_view_weak = new_entity_sprite_view;

    if (_entity_sprite_views.count(layer)) {
        _entity_sprite_views.at(layer).push_back(new_entity_sprite_view_weak);
    } else {
        _entity_sprite_views[layer] = {new_entity_sprite_view_weak};
    }

    entity->addObserver(new_entity_sprite_view);
}

void EntityViewCreator::createEntityTextView(std::shared_ptr<Entity> entity) {
    std::shared_ptr<EntityTextView> new_entity_text_view(new EntityTextView(entity));
    std::weak_ptr<EntityTextView> new_entity_text_view_weak = new_entity_text_view;

    _entity_text_views.push_back(new_entity_text_view_weak);

    entity->addObserver(new_entity_text_view);
}

std::vector<std::shared_ptr<EntitySpriteView>> EntityViewCreator::getEntitySpriteViews() {
    std::map<unsigned int, std::vector<std::weak_ptr<EntitySpriteView>>> new_entity_sprite_views;
    std::vector<std::shared_ptr<EntitySpriteView>> render_entity_sprite_views;

    for (const auto &[layer, layer_entity_views]: _entity_sprite_views) {
        std::vector<std::weak_ptr<EntitySpriteView>> new_layer_entity_views;

        for (const auto &entity_view: layer_entity_views) {
            if (!entity_view.expired()) {
                new_layer_entity_views.push_back(entity_view);

                render_entity_sprite_views.push_back(entity_view.lock());
            }
        }

        new_entity_sprite_views[layer] = new_layer_entity_views;
    }

    _entity_sprite_views = new_entity_sprite_views;

    return render_entity_sprite_views;
}

std::vector<std::shared_ptr<EntityTextView>> EntityViewCreator::getEntityTextViews() {
    std::vector<std::weak_ptr<EntityTextView>> new_entity_text_views;
    std::vector<std::shared_ptr<EntityTextView>> render_entity_text_views;

    for (const auto &entity_text_view: _entity_text_views) {
        if (!entity_text_view.expired()) {
            new_entity_text_views.push_back(entity_text_view);

            render_entity_text_views.push_back(entity_text_view.lock());
        }
    }

    _entity_text_views = new_entity_text_views;

    return render_entity_text_views;
}
