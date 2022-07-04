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
    initializeUIWidgets();
}

void World::initializeUIWidgets() {
//    // menu
    std::shared_ptr<UIWidget> menu_widget = std::make_shared<UIWidget>(UIWidget({0, 0}, _camera, {1, 1.5}));

    // view
    std::vector<std::string> menu_widget_textures = {"data/ui/prototype/menu.png"};
    AnimationStateMachine menu_widget_animation_state_machine = AnimationStateMachine();
    _entity_view_creator->createEntitySpriteView(menu_widget, menu_widget_textures, menu_widget_animation_state_machine,
                                                 10);

    _ui_widget_entities.push_back(menu_widget);

    // button
    std::shared_ptr<UIWidget> button_widget = std::make_shared<UIWidget>(UIWidget({0, 0}, _camera, {0.4, 0.15}));

    // view
    std::vector<std::string> button_widget_textures = {"data/ui/prototype/button.png"};
    AnimationStateMachine button_widget_animation_state_machine = AnimationStateMachine();
    _entity_view_creator->createEntitySpriteView(button_widget, button_widget_textures,
                                                 button_widget_animation_state_machine, 11);

    _ui_widget_entities.push_back(button_widget);
}

void World::initializeDoodle() {
    _player = std::make_shared<Doodle>(Doodle({1.5, 0.5}, _camera, {0.3, 0.3}));

    // view
    std::vector<std::string> player_textures = {
            "data/sprites/doodle/doodle-left.png",
            "data/sprites/doodle/doodle-right.png",
            "data/sprites/doodle/doodle-jump-left.png",
            "data/sprites/doodle/doodle-jump-right.png"
    };

    AnimationStateMachine player_animation_state_machine = AnimationStateMachine();
    _entity_view_creator->createEntitySpriteView(_player, player_textures, player_animation_state_machine, 0);
}

void World::updateUIEntities(double t, float dt) {
    for (const auto &ui_widget: _ui_widget_entities) {
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
