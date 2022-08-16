#include "World.h"

World::World(std::shared_ptr<IEntityViewCreator> entity_view_creator, float x_min, float x_max, float y_min,
             float y_max)
        : _camera(new Camera(x_min, x_max, y_min, y_max)), _entity_view_creator(std::move(entity_view_creator)),
          _force_static_update(true), _input_map(new InputMap) {
    loadResources();
    initializeUIWidgets();
    initializePhysicsEntities();
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

std::shared_ptr<InputMap> World::getUserInputMap() {
    return _input_map;
}

void World::loadResources() {
    loadAnimations();
    loadAudio();
}

void World::loadAnimations() {
    for (const auto &animation_data_group: animation_data_groups) {
        std::vector<std::string> texture_filenames;
        std::shared_ptr<std::map<std::string, AnimationPlayer>> animation_group =
                std::make_shared<std::map<std::string, AnimationPlayer>>();

        unsigned int current_texture_index = 0;

        for (const auto &animation_data_pair: animation_data_group.second) {
            AnimationResource animation_data = animation_data_pair.second;

            AnimationPlayer animation;
            animation.framerate = animation_data.framerate;
            animation.loop = animation_data.loop;

            for (const auto &texture_filename: animation_data.texture_filenames) {
                texture_filenames.push_back(texture_filename);

                animation.texture_indeces.push_back(current_texture_index);
                current_texture_index++;
            }

            animation_group->insert({animation_data_pair.first, animation});
        }

        _animation_groups[animation_data_group.first] = animation_group;
        _entity_view_creator->loadTextureGroup(animation_data_group.first, texture_filenames);
    }
}

void World::loadAudio() {

}

void World::initializeUIWidgets() {
    // background
    _ui_widget_entities.push_back(std::make_shared<UIWidget>(
            UIWidget({0, 1.5f}, _camera, {_camera->getWidth(), _camera->getHeight()},
                     _animation_groups["background"])));
    _entity_view_creator->createEntitySpriteView(_ui_widget_entities.back(), "background", 1);
}

void World::initializePhysicsEntities() {
    // player
    float scale_mul = 2.5f;
    _player = std::make_shared<Doodle>(
            Doodle({0.f, 2.5f}, _camera, {0.3f * scale_mul, 0.222f * scale_mul}, _animation_groups["adventurer"],
                   _input_map, 1, false));
    _entity_view_creator->createEntitySpriteView(_player, "adventurer", 5);

//    // walls
//    _walls.push_back(std::make_shared<Wall>(
//            Wall({-0.5f, 0.5f}, _camera, {0.4f, 0.4f}, _animation_groups["wall"])));
//    _entity_view_creator->createEntitySpriteView(_walls.back(), "wall", 3);
//
//    // portal radio music object
//    _portal_radios.push_back(
//            std::make_shared<PortalRadio>(PortalRadio({0.5f, 2}, _camera, {0.2f, 0.2f}, _animation_groups["portal_radio"])));
//    _entity_view_creator->createEntitySpriteView(_portal_radios.back(), "portal_radio", 4);

    // physics test scene
    // walls

    _walls.push_back(std::make_shared<Wall>(
            Wall({-0.5f, 0.f}, _camera, {1.f, 1.f}, _animation_groups["wall"], 1, false)));
    _entity_view_creator->createEntitySpriteView(_walls.back(), "wall", 3);

    _walls.push_back(std::make_shared<Wall>(
            Wall({0.5f, 0.f}, _camera, {1.f, 1.f}, _animation_groups["wall"], 1, false)));
    _entity_view_creator->createEntitySpriteView(_walls.back(), "wall", 3);

    _walls.push_back(std::make_shared<Wall>(
            Wall({0.5f, 1.5f}, _camera, {0.5f, 0.5f}, _animation_groups["wall"], 1, false)));
    _entity_view_creator->createEntitySpriteView(_walls.back(), "wall", 2);
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

    // collisions
    if (_player) {
        for (const auto &wall: _walls) {
            handleCollision(_player, wall, true);
        }
    }

    handleCollision(_walls.front(), _walls.back());
}

void World::updatePhysicsEntities(double t, float dt) {
    // player
    if (_player != nullptr) {
        _player->update(t, dt);
    }

    // walls
    for (const auto &wall: _walls) {
        wall->update(t, dt);
    }

    // portal radios
    for (const auto &portal_radio: _portal_radios) {
        portal_radio->update(t, dt);
    }

    // platforms

    // background tiles

    // bonuses

    // enemies

}

bool World::handleCollision(const std::shared_ptr<PhysicsEntity> &entity1,
                            const std::shared_ptr<PhysicsEntity> &entity2,
                            bool resolve) {
    if (entity1->getHitbox()->empty() || entity2->getHitbox()->empty()) {
        return false;
    }

//    std::cout << entity1->getHitbox()->getDisplacementToCollision(*entity2->getHitbox()) << std::endl;

    bool collided = entity1->getHitbox()->collides(*entity2->getHitbox());

    if (collided && resolve) {
        entity1->resolveCollision(*entity2);
    }

    return collided;
    return false;
}
