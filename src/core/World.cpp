#include "World.h"

World::World(std::shared_ptr<IEntityViewCreator> entity_view_creator, float x_min, float x_max, float y_min,
             float y_max)
        : _camera(new Camera(x_min, x_max, y_min, y_max)), _entity_view_creator(std::move(entity_view_creator)),
          _force_update(true), _user_input_map(new InputMap) {

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

    // update physics entities
    Stopwatch::getInstance().increaseAccumulator();

    while (Stopwatch::getInstance().getAccumulator() >= Stopwatch::getInstance().getPhysicsDeltaTime()) {
        updatePhysics(Stopwatch::getInstance().getPhysicsTime(), Stopwatch::getInstance().getPhysicsDeltaTime());

        Stopwatch::getInstance().increasePhysicsTime();
        Stopwatch::getInstance().decreaseAccumulator();
    }
}

void World::updateScreenResolution(float x_min, float x_max, float y_min, float y_max) {
    _camera->setScreenBoundaries(x_min, x_max, y_min, y_max);
    _force_update = true;
}

void World::initializeEntities() {
    initializeDoodle();
    initializeUIWidgets();
}

void World::initializeUIWidgets() {
    // background
    std::shared_ptr<UIWidget> background_widget = std::make_shared<UIWidget>(
            UIWidget({0, 0}, _camera, {_camera->getWidth(), _camera->getHeight()}));

    std::vector<std::string> background_widget_textures = {"data/prototype/tiles/Dark/texture_01.png"};
    _entity_view_creator->createEntitySpriteView(background_widget, background_widget_textures, 1);

    _ui_widget_entities.push_back(background_widget);

//    // menu
//    std::shared_ptr<UIWidget> menu_widget = std::make_shared<UIWidget>(UIWidget({0, 0}, _camera, {1, 1.5}));
//
//    std::vector<std::string> menu_widget_textures = {"data/prototype/ui/menu.png"};
//    AnimationStateMachine menu_widget_animation_state_machine = AnimationStateMachine();
//    _entity_view_creator->createEntitySpriteView(menu_widget, menu_widget_textures, menu_widget_animation_state_machine,
//                                                 10);
//
//    _ui_widget_entities.push_back(menu_widget);
//
//    // button
//    std::shared_ptr<UIWidget> button_widget = std::make_shared<UIWidget>(UIWidget({0, 0}, _camera, {0.4, 0.15}));
//
//    std::vector<std::string> button_widget_textures = {"data/prototype/ui/button.png"};
//    AnimationStateMachine button_widget_animation_state_machine = AnimationStateMachine();
//    _entity_view_creator->createEntitySpriteView(button_widget, button_widget_textures,
//                                                 button_widget_animation_state_machine, 11);
//
//    _ui_widget_entities.push_back(button_widget);
}

void World::initializeDoodle() {
    _player = std::make_shared<Doodle>(Doodle({0, 0}, _camera, {0.3 * 2, 0.219 * 2}));

    // view
    std::vector<std::string> player_textures = {
            "data/sprites/characters/doodle/doodle-left.png",
            "data/sprites/characters/doodle/doodle-right.png",
            "data/sprites/characters/doodle/doodle-jump-left.png",
            "data/sprites/characters/doodle/doodle-jump-right.png"
    };

    _entity_view_creator->createEntitySpriteView(_player, player_textures, 2);
}

void World::updateUIEntities(double t, float dt) {
    for (const auto &ui_widget: _ui_widget_entities) {
        if (!ui_widget->is_static() || _force_update) {
            ui_widget->update(t, dt);
            if (_force_update) _force_update = false;
        }
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
