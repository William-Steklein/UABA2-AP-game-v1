#include "World.h"

World::World(float x_min, float x_max, float y_min, float y_max,
             std::shared_ptr<IEntityViewCreator> entity_view_creator,
             std::shared_ptr<IEntityAudioCreator> entity_audio_creator)
        : _camera(new Camera(x_min, x_max, y_min, y_max)), _entity_view_creator(std::move(entity_view_creator)),
          _entity_audio_creator(std::move(entity_audio_creator)), _force_static_view_update(true),
          _input_map(new InputMap), _audio_listener_position(new Vector2f(0, 0)) {
    loadResources();
    initializeUIWidgets();
    initializePhysicsEntities();
}

World::~World() = default;

void World::sleep() {
    Stopwatch::getInstance().sleep_frame();
}

void World::update() {
    if (_input_map->z) {
        Stopwatch::getInstance().setPhysicsSpeed(1);
    }
    if (_input_map->x) {
        Stopwatch::getInstance().setPhysicsSpeed(1.f / 60);
    }

    // update UI entities
    updateUIEntities(Stopwatch::getInstance().getPhysicsTime(), Stopwatch::getInstance().getDeltaTime());

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
    updateSidebars();

    _force_static_view_update = true;
}

std::shared_ptr<InputMap> World::getUserInputMap() {
    return _input_map;
}

void World::loadResources() {
    loadTextures();
    loadAnimations();
    loadAudio();
}

void World::loadTextures() {
    for (const auto &texture_resource: texture_data) {
        _animation_players[texture_resource.first] = AnimationPlayer(texture_resource.first);
        _entity_view_creator->loadTextureGroup(texture_resource.first, {texture_resource.second});
    }
}

void World::loadAnimations() {
    for (const auto &animation_group_data: animation_groups_data) {
        std::vector<std::string> texture_filenames;
        AnimationPlayer animation_player(animation_group_data.first);

        unsigned int current_texture_index = 0;
        for (const auto &animation_data_pair: animation_group_data.second) {
            AnimationResource animation_data = animation_data_pair.second;

            Animation animation;
            animation.framerate = animation_data.framerate;
            animation.loop = animation_data.loop;

            for (const auto &texture_filename: animation_data.texture_filenames) {
                texture_filenames.push_back(texture_filename);

                animation.texture_indeces.push_back(current_texture_index);
                current_texture_index++;
            }

            animation_player.addAnimation(animation_data_pair.first, animation);
        }

        _animation_players.insert({animation_group_data.first, animation_player});
        _entity_view_creator->loadTextureGroup(animation_group_data.first, texture_filenames);
    }
}

void World::loadAudio() {
    _audio_player.setAudioListenerPosition(_audio_listener_position);
    _audio_player.setMaxDistance(2.f);

    for (const auto &audio_resource: audio_sound_data) {
        unsigned int sound_id = _entity_audio_creator->loadSound(audio_resource.second);

        _audio_player.addSound(sound_id, audio_resource.first);
    }

    for (const auto &audio_resource: audio_music_data) {
        unsigned int music_id = _entity_audio_creator->loadMusic(audio_resource.second);

        _audio_player.addMusic(music_id, audio_resource.first);
    }
}

void World::initializeUIWidgets() {
    // sidebars
    for (int i = 0; i < 2; i++) {
        _ui_widget_entities.push_back(std::make_shared<UIWidget>(
                UIWidget({0, 0}, _camera, {1, 1}, _animation_players["sidescreen_background"])));
        _entity_view_creator->createEntitySpriteView(_ui_widget_entities.back(), 200);
        _side_bars.push_back(_ui_widget_entities.back());
    }

    updateSidebars();

    // background
    _ui_widget_entities.push_back(std::make_shared<UIWidget>(
            UIWidget({0, 1.5f}, _camera, {_camera->getWidth(), _camera->getHeight()},
                     _animation_players["background"])));
    _entity_view_creator->createEntitySpriteView(_ui_widget_entities.back(), 1);
}

void World::updateSidebars() {
    if (_camera->isSidescreenHorizontal()) {
        // left and right
        Vector2f left_bottom_left = _camera->projectCoordSubscreenToCore(
                {_camera->getScreenXBoundaries().x, _camera->getScreenYBoundaries().x});
        Vector2f left_bottom_right = {_camera->getXBounderies().x, _camera->getYBounderies().x};
        Vector2f left_top_left = _camera->projectCoordSubscreenToCore(
                {_camera->getScreenXBoundaries().x, _camera->getScreenYBoundaries().y});

        Vector2f right_bottom_left = {_camera->getXBounderies().y, _camera->getYBounderies().x};
        Vector2f right_bottom_right = _camera->projectCoordSubscreenToCore(
                {_camera->getScreenXBoundaries().y, _camera->getScreenYBoundaries().x});
        Vector2f right_top_left = {_camera->getXBounderies().y, _camera->getYBounderies().y};

        _side_bars.front()->setPosition(
                {(left_bottom_left.x + left_bottom_right.x) / 2, (left_bottom_left.y + left_top_left.y) / 2});
        _side_bars.front()->setScale({left_bottom_right.x - left_bottom_left.x, left_top_left.y - left_bottom_left.y});

        _side_bars.back()->setPosition(
                {(right_bottom_left.x + right_bottom_right.x) / 2, (right_bottom_left.y + right_top_left.y) / 2});
        _side_bars.back()->setScale(
                {right_bottom_right.x - right_bottom_left.x, right_top_left.y - right_bottom_left.y});

    } else {
        Vector2f bottom_bottom_left = _camera->projectCoordSubscreenToCore(
                {_camera->getScreenXBoundaries().x, _camera->getScreenYBoundaries().x});
        Vector2f bottom_bottom_right = _camera->projectCoordSubscreenToCore(
                {_camera->getScreenXBoundaries().y, _camera->getScreenYBoundaries().x});
        Vector2f bottom_top_left = {_camera->getXBounderies().x, _camera->getYBounderies().x};

        Vector2f top_bottom_left = {_camera->getXBounderies().x, _camera->getYBounderies().y};
        Vector2f top_bottom_right = {_camera->getXBounderies().y, _camera->getYBounderies().y};
        Vector2f top_top_left = _camera->projectCoordSubscreenToCore(
                {_camera->getScreenXBoundaries().x, _camera->getScreenYBoundaries().y});

        _side_bars.front()->setPosition(
                {(bottom_bottom_left.x + bottom_bottom_right.x) / 2, (bottom_bottom_left.y + bottom_top_left.y) / 2});
        _side_bars.front()->setScale(
                {bottom_bottom_right.x - bottom_bottom_left.x, bottom_top_left.y - bottom_bottom_left.y});

        _side_bars.back()->setPosition(
                {(top_bottom_left.x + top_bottom_right.x) / 2, (top_bottom_left.y + top_top_left.y) / 2});
        _side_bars.back()->setScale({top_bottom_right.x - top_bottom_left.x, top_top_left.y - top_bottom_left.y});
    }
}

void World::initializePhysicsEntities() {
    // player
    float scale_mul = 2.f;
    _player = std::make_shared<Doodle>(
            Doodle({0.f, 2.5f}, _camera, {0.3f * scale_mul, 0.222f * scale_mul}, _input_map,
                   _animation_players["adventurer"], _audio_player));
    _entity_view_creator->createEntitySpriteView(_player, 5);
    _entity_audio_creator->createEntityAudio(_player);

    // portal radio music object
    _portal_radios.push_back(
            std::make_shared<PortalRadio>(
                    PortalRadio({0.5f, 2.5f}, _camera, {0.2f, 0.2f}, _animation_players["portal_radio"], _audio_player)));
    _entity_view_creator->createEntitySpriteView(_portal_radios.back(), 4);
    _entity_audio_creator->createEntityAudio(_portal_radios.back());

    // walls
    _walls.push_back(std::make_shared<Wall>(
            Wall({-0.5f, 0.f}, _camera, {1.f, 1.f}, _animation_players["wall"], {}, true)));
    _entity_view_creator->createEntitySpriteView(_walls.back(), 3);

    _walls.push_back(std::make_shared<Wall>(
            Wall({0.5f, 0.f}, _camera, {1.f, 1.f}, _animation_players["wall"], {}, true)));
    _entity_view_creator->createEntitySpriteView(_walls.back(), 3);
}

void World::updateUIEntities(double t, float dt) {
    for (const auto &ui_widget: _ui_widget_entities) {
        if (!ui_widget->is_static_view() || _force_static_view_update) {
            ui_widget->update(t, dt);
        }
    }
    if (_force_static_view_update) _force_static_view_update = false;
}

void World::updatePhysics(double t, float dt) {
    updatePhysicsEntities(t, dt);

    // collisions
    if (_player) {
        for (const auto &wall: _walls) {
            handleCollision(_player, wall, true);

            for (const auto &ray: _player->getRays()) {
                handleCollision(ray, wall);
            }
        }

        for (const auto &portal_radio: _portal_radios) {
            handleCollision(_player, portal_radio);

            for (const auto &ray: _player->getRays()) {
                handleCollision(ray, portal_radio);
            }
        }
    }

    for (const auto &portal_radio: _portal_radios) {
        for (const auto &wall: _walls) {
            handleCollision(portal_radio, wall, true);
        }
    }
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

    // audio listener
    if (_player != nullptr) {
        *_audio_listener_position = _player->getPosition();
    } else {
        *_audio_listener_position = {0, 0};
    }
}

bool World::handleCollision(const std::shared_ptr<PhysicsEntity> &entity1,
                            const std::shared_ptr<PhysicsEntity> &entity2,
                            bool resolve) {
    if (entity1->getHitbox()->empty() || entity2->getHitbox()->empty()) {
        return false;
    }

    bool collided = entity1->getHitbox()->collides(*entity2->getHitbox());

    if (collided && resolve) {
        entity1->resolveCollision(*entity2);
    }

    return collided;
}

bool World::handleCollision(const std::shared_ptr<Ray> &ray, const std::shared_ptr<PhysicsEntity> &entity) {
    if (entity->getHitbox()->empty()) {
        return false;
    }

    return ray->collides(*entity->getHitbox());
}
