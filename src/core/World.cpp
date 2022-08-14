#include "World.h"

World::World(std::shared_ptr<IEntityViewCreator> entity_view_creator, float x_min, float x_max, float y_min,
             float y_max)
        : _camera(new Camera(x_min, x_max, y_min, y_max)), _entity_view_creator(std::move(entity_view_creator)),
          _force_static_update(true), _user_input_map(new InputMap) {
    loadAnimations();
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

void World::loadAnimations() {
    for (const auto &animation_data_group: animation_data_groups) {
        std::vector<std::string> texture_filenames;
        std::shared_ptr<std::map<std::string, Animation>> animation_group =
                std::make_shared<std::map<std::string, Animation>>();

        unsigned int current_texture_index = 0;

        for (const auto &animation_data_pair: animation_data_group.second) {
            AnimationData animation_data = animation_data_pair.second;

            Animation animation;
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

void World::initializeEntities() {
    initializeUIWidgets();
    initializeDoodle();

    std::shared_ptr<Wall> new_wall = std::make_shared<Wall>(
            Wall({-0.3f, 1.f}, _camera, {0.4f, 0.4f}, _animation_groups["wall"]));
    _entity_view_creator->createEntitySpriteView(new_wall, "wall", 3);
    _walls.push_back(new_wall);
}

void World::initializeUIWidgets() {
    // background
    std::shared_ptr<UIWidget> background_widget = std::make_shared<UIWidget>(
            UIWidget({0, 1.5f}, _camera, {_camera->getWidth(), _camera->getHeight()}, _animation_groups["background"]));

    _entity_view_creator->createEntitySpriteView(background_widget, "background", 1);
    _ui_widget_entities.push_back(background_widget);
}

void World::initializeDoodle() {
    float scale_mul = 2.5f;
    _player = std::make_shared<Doodle>(
            Doodle({0.f, 1.f}, _camera, {0.3f * scale_mul, 0.222f * scale_mul}, _animation_groups["adventurer"],
                   _user_input_map, 1, true));
    _entity_view_creator->createEntitySpriteView(_player, "adventurer", 2);
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
    for (const auto &wall: _walls) {
        handleCollision(_player, wall, true);
    }
}

void World::updatePhysicsEntities(double t, float dt) {
    // player
    _player->update(t, dt);

    // walls
    for (const auto &wall: _walls) {
        wall->update(t, dt);
    }

    // platforms

    // background tiles

    // bonuses

    // enemies

}

std::shared_ptr<InputMap> World::getUserInputMap() {
    return _user_input_map;
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
}
