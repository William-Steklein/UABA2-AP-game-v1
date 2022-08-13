#include "World.h"

World::World(std::shared_ptr<IEntityViewCreator> entity_view_creator, float x_min, float x_max, float y_min,
             float y_max)
        : _camera(new Camera(x_min, x_max, y_min, y_max)), _entity_view_creator(std::move(entity_view_creator)),
          _force_static_update(true), _user_input_map(new InputMap) {
    loadTextureGroups();
    initializeEntities();
}

World::~World() = default;

void World::sleep() {
    Stopwatch::getInstance().sleep_frame();
}

void World::update() {
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
    _force_static_update = true;
}

void World::loadTextureGroups() {
    std::vector<std::string> player_textures = {
            "data/sprites/doodle/doodle-left.png",
            "data/sprites/doodle/doodle-right.png",
            "data/sprites/doodle/doodle-jump-left.png",
            "data/sprites/doodle/doodle-jump-right.png",
            "data/sprites/circle_explosion/Circle_explosion1.png",
            "data/sprites/circle_explosion/Circle_explosion2.png",
            "data/sprites/circle_explosion/Circle_explosion3.png",
            "data/sprites/circle_explosion/Circle_explosion4.png",
            "data/sprites/circle_explosion/Circle_explosion5.png",
            "data/sprites/circle_explosion/Circle_explosion6.png",
            "data/sprites/circle_explosion/Circle_explosion7.png",
            "data/sprites/circle_explosion/Circle_explosion8.png",
            "data/sprites/circle_explosion/Circle_explosion9.png",
            "data/sprites/circle_explosion/Circle_explosion10.png",
    };

    std::vector<std::string> background_widget_textures = {"data/textures/prototype/Dark/texture_07.png"};

    _entity_view_creator->loadTextureGroup("player", player_textures);
    _entity_view_creator->loadTextureGroup("background", background_widget_textures);

    std::map<std::string, AnimationData> player_animations = {
            {"idle_standing_left", {{0}, 0, true}},
            {"idle_standing_right", {{1}, 0, true}},
            {"idle_jumping_left", {{2}, 0, true}},
            {"idle_jumping_right", {{3}, 0, true}},
            {"explosion", {{4, 5, 6, 7, 8, 9, 10, 11, 12, 13}, 0.25f, false}},
    };
}

void World::initializeEntities() {
    initializeDoodle();
    initializeUIWidgets();
}

void World::initializeUIWidgets() {
    // background
    std::shared_ptr<UIWidget> background_widget = std::make_shared<UIWidget>(
            UIWidget({0, 0}, _camera, {_camera->getWidth(), _camera->getHeight()}));

    _entity_view_creator->createEntitySpriteView(background_widget, "background", 1);
    _ui_widget_entities.push_back(background_widget);

//
//    // menu
//    std::shared_ptr<UIWidget> menu_widget = std::make_shared<UIWidget>(UIWidget({0, 0}, _camera, {1, 1.5}));
//
//    std::vector<std::string> menu_widget_textures = {"data/prototype/ui/menu.png"};
//    _entity_view_creator->createEntitySpriteView(menu_widget, menu_widget_textures, 10);
//
//    _ui_widget_entities.push_back(menu_widget);
//
//    // button
//    std::shared_ptr<UIWidget> button_widget = std::make_shared<UIWidget>(UIWidget({0, 0}, _camera, {0.4, 0.15}));
//
//    std::vector<std::string> button_widget_textures = {"data/prototype/ui/button.png"};
//    _entity_view_creator->createEntitySpriteView(button_widget, button_widget_textures, 11);
//
//    _ui_widget_entities.push_back(button_widget);
}

void World::initializeDoodle() {
    float scale_mul = 5.f;
    _player = std::make_shared<Doodle>(Doodle({0, 0}, _camera, {0.3f * scale_mul, 0.219f * scale_mul}));
    _entity_view_creator->createEntitySpriteView(_player, "player", 100);
}

void World::updateUIEntities(double t, float dt) {
    for (const auto &ui_widget: _ui_widget_entities) {
        if (!ui_widget->is_static() || _force_static_update) {
            ui_widget->update(t, dt);
        }
    }
    if (_force_static_update) _force_static_update = false;
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
