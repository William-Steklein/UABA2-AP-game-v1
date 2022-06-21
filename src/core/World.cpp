#include "World.h"
#include "animation/AnimationStateMachine.h"
#include "entities/IEntityViewCreator.h"

World::World(std::shared_ptr<IEntityViewCreator> entity_view_creator, float x_min, float x_max, float y_min,
             float y_max)
        : _entity_view_creator(std::move(entity_view_creator)), _user_input_map(new InputMap), _camera(new Camera) {
    _camera->setGameBoundaries(x_min, x_max, y_min, y_max);

    _player = std::make_shared<Doodle>(Doodle({0, 0}, _camera, {0.3, 0.3}));

    std::vector<std::string> player_textures = {
            "data/sprites/doodle/doodle-left.png",
            "data/sprites/doodle/doodle-right.png",
            "data/sprites/doodle/doodle-jump-left.png",
            "data/sprites/doodle/doodle-jump-right.png"
    };

    AnimationStateMachine player_animation_state_machine = AnimationStateMachine();
    _entity_view_creator->createEntityView(_player, player_textures, player_animation_state_machine, 0);
}

World::~World() = default;

void World::update(double t, float dt) {
    updateEntities(t, dt);
}

void World::updateEntities(double t, float dt) {
    // player

    // platforms

    // background tiles

    // bonuses

    // monsters

}

std::shared_ptr<InputMap> World::getUserInputMap() {
    return _user_input_map;
}
