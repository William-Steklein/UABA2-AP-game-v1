#include "EntityViewCreator.h"

void EntityViewCreator::createEntityView(std::shared_ptr<Entity> entity, std::vector<std::string> texture_files,
                                         AnimationStateMachine animation_state_machine, unsigned int layer) {
    std::shared_ptr<EntityView> new_entity_view(new EntityView(entity, texture_files, animation_state_machine));
    std::weak_ptr<EntityView> new_entity_view_weak = new_entity_view;

    if (_entity_views.count(layer)) {
        _entity_views.at(layer).push_back(new_entity_view_weak);
    } else {
        _entity_views[layer] = {new_entity_view_weak};
    }

    entity->addObserver(new_entity_view);
}

std::vector<std::shared_ptr<EntityView>> EntityViewCreator::getEntityViews() {
    std::map<unsigned int, std::vector<std::weak_ptr<EntityView>>> new_entity_views;
    std::vector<std::shared_ptr<EntityView>> render_entity_views;

    for (const auto &[layer, layer_entity_views] : _entity_views) {
        std::vector<std::weak_ptr<EntityView>> new_layer_entity_views;

        for (const auto &entity_view : layer_entity_views) {
            if (!entity_view.expired()) {
                new_layer_entity_views.push_back(entity_view);

                std::shared_ptr<EntityView> render_entity_view = entity_view.lock();
                render_entity_views.push_back(render_entity_view);
            }
        }

        new_entity_views[layer] = new_layer_entity_views;
    }

    _entity_views = new_entity_views;

    return render_entity_views;
}
