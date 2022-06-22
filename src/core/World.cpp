#include "World.h"

World::World(std::shared_ptr<IEntityViewCreator> entity_view_creator, float x_min, float x_max, float y_min,
             float y_max)
        : _entity_view_creator(std::move(entity_view_creator)), _user_input_map(new InputMap), _camera(new Camera) {
    _camera->setGameBoundaries(x_min, x_max, y_min, y_max);

    initializeEntities();
}

World::~World() = default;

void World::sleep() {
    Stopwatch::getInstance().sleep_frame();
}

void World::update() {
    // dispatch events from event manager

    // update UI entities
    updateUIEntities(Stopwatch::getInstance().getPhysicsTime(), Stopwatch::getInstance().getAccumulator());

    Stopwatch::getInstance().increaseAccumulator();

    while (Stopwatch::getInstance().getAccumulator() >= Stopwatch::getInstance().getPhysicsDeltaTime()) {
        updatePhysics(Stopwatch::getInstance().getPhysicsTime(), Stopwatch::getInstance().getPhysicsDeltaTime());

         Stopwatch::getInstance().increasePhysicsTime();
         Stopwatch::getInstance().decreaseAccumulator();
    }
}

void World::initializeEntities() {
    initializeDoodle();
    initializeUIWidget();
}

void World::initializeUIWidget() {
    std::shared_ptr<UIWidget> new_ui_widget = std::make_shared<UIWidget>(UIWidget({-1, 0}, _camera, {0.2, 0.2}));

    // view
    std::vector<std::string> ui_widget_textures = {"data/ui/test1.png"};

    AnimationStateMachine ui_widget_animation_state_machine = AnimationStateMachine();
    _entity_view_creator->createEntitySpriteView(new_ui_widget, ui_widget_textures, ui_widget_animation_state_machine, 10);

    _ui_widget_entities.push_back(new_ui_widget);
}

void World::initializeDoodle() {
    _player = std::make_shared<Doodle>(Doodle({0, 0.5}, _camera, {0.3, 0.3}));

    // view
    std::vector<std::string> player_textures = {
            "data/sprites/doodle/doodle-left.png",
            "data/sprites/doodle/doodle-right.png",
            "data/sprites/doodle/doodle-jump-left.png",
            "data/sprites/doodle/doodle-jump-right.png"
    };

    AnimationStateMachine player_animation_state_machine = AnimationStateMachine();
    _entity_view_creator->createEntitySpriteView(_player, player_textures, player_animation_state_machine, 0);

    // actions
//    _event_manager.addListener("ACTION_JUMP", pJumpFunc)
//    _event_manager.addListener("ACTION_MOVE_LEFT", pJumpFunc)
//    _event_manager.addListener("ACTION_MOVE_RIGHT", pJumpFunc)
}

void World::updateUIEntities(double t, float dt) {
    for (const auto &ui_widget : _ui_widget_entities) {
        ui_widget->update(t, dt);
    }
}

void World::updatePhysics(double t, float dt) {
    updatePhysicsEntities(t, dt);
}

void World::updatePhysicsEntities(double t, float dt) {
    // player
    _player->update(t, dt);

    // platforms

    // background tiles

    // bonuses

    // enemies

}

std::shared_ptr<InputMap> World::getUserInputMap() {
    return _user_input_map;
}
