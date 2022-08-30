#include "World.h"

World::World(float x_min, float x_max, float y_min, float y_max,
             std::shared_ptr<IEntityViewCreator> entity_view_creator,
             std::shared_ptr<IEntityAudioCreator> entity_audio_creator)
        : _camera(new Camera(x_min, x_max, y_min, y_max)), _entity_view_creator(std::move(entity_view_creator)),
          _entity_audio_creator(std::move(entity_audio_creator)), _force_static_view_update(true),
          _input_map(new InputMap), _audio_listener_position(new Vector2f(0, 0)),
          _start_debug_mode(new bool(false)), _debug_mode(false),
          _start_doodle_mode(new bool(false)), _doodle_mode(false),
          _start_pauze_overlay(new bool(false)), _pauze_overlay(false), _start_main_menu(new bool(false)),
          _score(new Score()), _resume(new bool(false)), _gameover(false), _start_gameover(false),
          _last_platform_y_pos(-1.f), _last_bg_tile_y_pos(-1.f),
          _screen_ui_tree(craeteEmptyScreenUI()), _ingame_ui_tree(craeteEmptyScreenUI()) {

    loadResources();
    initializeSideBars();

    loadStartMenu();
}

World::~World() = default;

void World::sleep() {
    Stopwatch::getInstance().sleep_frame();
}

void World::update() {
    gameUpdate(Stopwatch::getInstance().getPhysicsTime(), Stopwatch::getInstance().getDeltaTime());

    if (!_pauze_overlay) {
        Stopwatch::getInstance().increaseAccumulator();
        while (Stopwatch::getInstance().getAccumulator() >= Stopwatch::getInstance().getPhysicsDeltaTime()) {
            physicsUpdate(Stopwatch::getInstance().getPhysicsTime(), Stopwatch::getInstance().getPhysicsDeltaTime());

            Stopwatch::getInstance().increasePhysicsTime();
            Stopwatch::getInstance().decreaseAccumulator();
        }
    }
}

void World::updateScreenResolution(float x_min, float x_max, float y_min, float y_max) {
    _camera->setScreenBoundaries(x_min, x_max, y_min, y_max);
    updateSidebars();

    _force_static_view_update = true;
}

void World::updateMousePosition(float x, float y) {
    _input_map->mouse_pos_core = _camera->projectCoordScreenToCore({x, y});
//    std::cout << _input_map->mouse_pos_core << std::endl;
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

void World::initializeSideBars() {
    // sidebars
    for (int i = 0; i < 2; i++) {
        _side_bars.push_back(std::make_shared<UIEntity>(
                UIEntity({0, 0}, _camera, {1, 1}, _animation_players["black"])));
        _entity_view_creator->createEntitySpriteView(_side_bars.back(), 200);
    }

    updateSidebars();
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

void World::clear() {
    _camera->reset();
    _score->reset();

    _physics_entities.clear();
    _player = nullptr;
    _walls.clear();
    _platforms.clear();
    _last_platform_y_pos = -1.f;
    _bonuses.clear();
    _active_bonus = nullptr;
    _portal_radios.clear();
    _player_bullets.clear();
    _enemy_bullets.clear();

    _ui_entities.clear();
    _screen_ui_tree = craeteEmptyScreenUI();
    _ui_entities.push_back(_screen_ui_tree);
    _ingame_ui_tree = craeteEmptyScreenUI();
    _ui_entities.push_back(_ingame_ui_tree);

    _bg_tiles.clear();
    _buttons.clear();
    _last_bg_tile_y_pos = -1.f;
    _buttons.clear();
    _enemy_hp_bars.clear();
}

void World::gameUpdate(double t, float dt) {
    // game flow
    if (*_start_main_menu) {
        *_start_main_menu = false;
        _debug_mode = false;
        _doodle_mode = false;
        _pauze_overlay = false;
        clear();
        loadStartMenu();
    }

    if (*_start_debug_mode) {
        *_start_debug_mode = false;
        _pauze_overlay = false;
        startDebugMode();
    } else if (*_start_doodle_mode) {
        *_start_doodle_mode = false;
        _pauze_overlay = false;
        startDoodleMode();
    }

    if ((_debug_mode || _doodle_mode) && (*_start_pauze_overlay || _input_map->esc) && !_gameover) {
        *_start_pauze_overlay = false;
        _screen_ui_tree = craeteEmptyScreenUI();
        _ui_entities.push_back(_screen_ui_tree);

        startPauzeOverlay();
    }

    if (_pauze_overlay && *_resume) {
        *_resume = false;
        _pauze_overlay = false;

        _screen_ui_tree = craeteEmptyScreenUI();
        _ui_entities.push_back(_screen_ui_tree);

        loadPauseOverlayButton();
    }

    if ((_debug_mode || _doodle_mode) && _start_gameover) {
        _screen_ui_tree = craeteEmptyScreenUI();
        _ui_entities.push_back(_screen_ui_tree);

        startGameOverMode();
    }

    handleUpdatePhysicsSpeed();
    updateUIEntities(t, dt);
}

void World::updateUIEntities(double t, float dt) {
    // update sidebars
    if (_force_static_view_update) {
        for (const auto &sidebar: _side_bars) {
            sidebar->update(t, dt);
        }
    }

    // update ui entities and delete expired
    for (auto iter = _ui_entities.begin(); iter != _ui_entities.end();) {
        if (iter->expired()) {
            iter = _ui_entities.erase(iter);
        } else {
            std::shared_ptr<UIEntity> ui_widget = iter->lock();
            if (!ui_widget->isStaticView() || _force_static_view_update) {
                ui_widget->update(t, dt);
            }

            iter++;
        }
    }

    // button mouse clicks
    if (_input_map->mouse_button_left) {
        for (auto iter = _buttons.begin(); iter != _buttons.end();) {
            if (iter->expired()) {
                iter = _buttons.erase(iter);
            } else {
                std::shared_ptr<Button> button = iter->lock();
                if (button->getHitbox() && button->getHitbox()->collides(_input_map->mouse_pos_core) &&
                    !_input_map->mouse_button_left_clicked) {
                    button->setPressed(true);
                    _input_map->mouse_button_left_clicked = true;
                }

                iter++;
            }
        }
    }

    // reset force static view update
    if (_force_static_view_update) _force_static_view_update = false;
}

void World::physicsUpdate(double t, float dt) {
    // game logic
    if (_gameover) {
        updateGameOverMode(t, dt);
    } else {
        if (_debug_mode) {
            updateDebugMode(t, dt);
        } else if (_doodle_mode) {
            updateDoodleMode(t, dt);
        }
    }

    // physics entities update
    updatePhysicsEntities(t, dt);
    // collisions update
    updatePhysicsCollisions();

    // update ui position
    _screen_ui_tree->setPosition(_camera->getPosition());
    _ingame_ui_tree->setPosition(_camera->getPosition());
}

void World::updatePhysicsEntities(double t, float dt) {
    // update physics entities and delete expired weak physics entities pointers
    for (auto iter = _physics_entities.begin(); iter != _physics_entities.end();) {
        if (iter->expired()) {
            iter = _physics_entities.erase(iter);
        } else {
            iter->lock()->update(t, dt);
            iter++;
        }
    }

    // audio listener
    if (_player != nullptr) {
        *_audio_listener_position = _player->getPosition();
    } else {
        *_audio_listener_position = {0, 0};
    }
}

void World::updatePhysicsCollisions() {
    // player bullets
    for (const auto &player_bullet: _player_bullets) {
        for (const auto &enemy_weak: _enemies) {
            std::shared_ptr<Enemy> enemy = enemy_weak.lock();
            if (enemy) {
                if (handleCollision(player_bullet, enemy, false, false)) {
                    player_bullet->disappear();
                    enemy->subtractHitPoints(1);

                    if (enemy->getCurrentHitPoints() > 0 && enemy->isShootBack()) {
                        spawnEnemyBullet(enemy->getPosition(), false);
                    }
                }
            }
        }
    }

    if (_player && !_gameover) {
        for (const auto &platform: _platforms) {
            handleCollision(_player, platform, true, true);

            for (const auto &ray: _player->getRays()) {
                if (handleCollision(ray, platform, false) && _player->getVelocity().y < 0) {
                    platform->setCollided();
                }
            }
        }

        // bonuses
        if (!_active_bonus) {
            for (const auto &bonus: _bonuses) {
                handleCollision(_player, bonus, true, false);

                if (bonus->isCollided()) {
                    bonus->applyEntity(_player);

                    if (bonus->isActive()) {
                        _active_bonus = bonus;
                    }
                }
            }
        }

        // enemy bullets
        for (const auto &enemy_bullet: _enemy_bullets) {
            if (handleCollision(enemy_bullet, _player, false, false)) {
                enemy_bullet->disappear();
                _player->subtractHitPoints(1);
                // todo: constants
                _score->substractScore(100);
            }
        }

        for (const auto &wall: _walls) {
            handleCollision(_player, wall);

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
            handleCollision(portal_radio, wall);
        }
    }
}

void World::handleUpdatePhysicsSpeed() {
    if (_input_map->z) {
        Stopwatch::getInstance().setPhysicsSpeed(1);
    }

    if (_input_map->x) {
        Stopwatch::getInstance().setPhysicsSpeed(1.f / 60);
    }
}

void World::loadStartMenu() {
    // ui screen and background
    _screen_ui_tree = std::make_shared<UIEntity>(
            UIEntity({0, 1.5f}, _camera, {_camera->getWidth(), _camera->getHeight()},
                     _animation_players["background"], {}, false));
    _ui_entities.push_back(_screen_ui_tree);
    _entity_view_creator->createEntitySpriteView(_screen_ui_tree, 1);

    // menu frame
    std::shared_ptr<UIEntity> menu = std::make_shared<UIEntity>(
            UIEntity({0, 0}, _camera, {1.f, 1.5f},
                     _animation_players["menu"]));
    _entity_view_creator->createEntitySpriteView(menu, 1);
    _screen_ui_tree->addChild(menu, _screen_ui_tree);

    // play button
    std::shared_ptr<Button> button = std::make_shared<Button>(
            Button({0, 0.5f}, _camera, {0.5f, 0.25f}, _animation_players["button"]));
    menu->addChild(button, menu);
    _buttons.push_back(button);
    _entity_view_creator->createEntitySpriteView(button, 2);
    _start_doodle_mode = button->getPressedPointer();

    std::shared_ptr<std::string> button_string = std::make_shared<std::string>("doodle jump");
    std::shared_ptr<TextBox> text_box = std::make_shared<TextBox>(
            TextBox({0, 0}, _camera, {0.5f, 0.25f}, button_string));
    button->addChild(text_box, button);
    _entity_view_creator->createEntityTextView(text_box);

    // debug button
    button = std::make_shared<Button>(Button({0, 0.125f}, _camera, {0.5f, 0.25f}, _animation_players["button"]));
    menu->addChild(button, menu);
    _buttons.push_back(button);
    _entity_view_creator->createEntitySpriteView(button, 2);
    _start_debug_mode = button->getPressedPointer();

    button_string = std::make_shared<std::string>("debug");
    text_box = std::make_shared<TextBox>(
            TextBox({0, 0}, _camera, {0.5f, 0.25f}, button_string));
    button->addChild(text_box, button);
    _entity_view_creator->createEntityTextView(text_box);
}

void World::loadPauseOverlayButton() {
    Vector2f button_size = {0.2f, 0.2f};
    std::shared_ptr<Button> button = std::make_shared<Button>(
            Button({_camera->getWidth() / 2 - button_size.x, _camera->getHeight() / 2 - button_size.y}, _camera,
                   button_size, _animation_players["hamburger"]));
    _screen_ui_tree->addChild(button, _screen_ui_tree);
    _buttons.push_back(button);
    _entity_view_creator->createEntitySpriteView(button, 500);
    _start_pauze_overlay = button->getPressedPointer();
}

void World::startPauzeOverlay() {
    _pauze_overlay = true;
    unsigned int layer = 500;

    // menu frame
    std::shared_ptr<UIEntity> menu = std::make_shared<UIEntity>(
            UIEntity({0, 0}, _camera, {1.f, 1.5f},
                     _animation_players["menu"]));
    _entity_view_creator->createEntitySpriteView(menu, layer);
    _screen_ui_tree->addChild(menu, _screen_ui_tree);

    // resume button
    std::shared_ptr button = std::make_shared<Button>(
            Button({0, 0.5f}, _camera, {0.5f, 0.25f}, _animation_players["button"]));
    menu->addChild(button, menu);
    _buttons.push_back(button);
    _entity_view_creator->createEntitySpriteView(button, layer + 1);
    _resume = button->getPressedPointer();

    std::shared_ptr<std::string> button_string = std::make_shared<std::string>("resume");
    std::shared_ptr<TextBox> text_box = std::make_shared<TextBox>(
            TextBox({0, 0}, _camera, {0.5f, 0.25f}, button_string));
    button->addChild(text_box, button);
    _entity_view_creator->createEntityTextView(text_box);

    // restart button
    button = std::make_shared<Button>(Button({0, 0.125f}, _camera, {0.5f, 0.25f}, _animation_players["button"]));
    menu->addChild(button, menu);
    _buttons.push_back(button);
    _entity_view_creator->createEntitySpriteView(button, layer + 1);
    if (_doodle_mode) {
        _start_doodle_mode = button->getPressedPointer();
    } else {
        _start_debug_mode = button->getPressedPointer();
    }

    button_string = std::make_shared<std::string>("restart");
    text_box = std::make_shared<TextBox>(
            TextBox({0, 0}, _camera, {0.5f, 0.25f}, button_string));
    button->addChild(text_box, button);
    _entity_view_creator->createEntityTextView(text_box);

    // return to menu button
    button = std::make_shared<Button>(Button({0, -0.25f}, _camera, {0.5f, 0.25f}, _animation_players["button"]));
    menu->addChild(button, menu);
    _buttons.push_back(button);
    _entity_view_creator->createEntitySpriteView(button, layer + 1);
    _start_main_menu = button->getPressedPointer();

    button_string = std::make_shared<std::string>("return\nto menu");
    text_box = std::make_shared<TextBox>(
            TextBox({0, 0}, _camera, {0.5f, 0.25f}, button_string));
    button->addChild(text_box, button);
    _entity_view_creator->createEntityTextView(text_box);
}

void World::startGameoverOverlay() {
    _pauze_overlay = true;
    unsigned int layer = 500;
    _ingame_ui_tree = craeteEmptyScreenUI();
    _ui_entities.push_back(_ingame_ui_tree);

    // menu
    std::shared_ptr<UIEntity> menu = std::make_shared<UIEntity>(
            UIEntity({0, 0}, _camera, {1.f, 1.5f},
                     _animation_players["menu"]));
    _entity_view_creator->createEntitySpriteView(menu, layer);
    _screen_ui_tree->addChild(menu, _screen_ui_tree);

    std::shared_ptr<std::string> score_string = std::make_shared<std::string>(
            "SCORE\n" + std::to_string(_score->getScore()));
    std::shared_ptr<TextBox> text_box = std::make_shared<TextBox>(
            TextBox({0, 0.5f}, _camera, {0.5f, 0.25f}, score_string));
    menu->addChild(text_box, menu);
    _entity_view_creator->createEntityTextView(text_box);

    std::shared_ptr button = std::make_shared<Button>(
            Button({0, 0.125f}, _camera, {0.5f, 0.25f}, _animation_players["button"]));
    menu->addChild(button, menu);
    _buttons.push_back(button);
    _entity_view_creator->createEntitySpriteView(button, layer + 1);
    if (_doodle_mode) {
        _start_doodle_mode = button->getPressedPointer();
    } else {
        _start_debug_mode = button->getPressedPointer();
    }

    std::shared_ptr<std::string> button_string = std::make_shared<std::string>("restart");
    text_box = std::make_shared<TextBox>(
            TextBox({0, 0}, _camera, {0.5f, 0.25f}, button_string));
    button->addChild(text_box, button);
    _entity_view_creator->createEntityTextView(text_box);

    button = std::make_shared<Button>(Button({0, -0.25f}, _camera, {0.5f, 0.25f}, _animation_players["button"]));
    menu->addChild(button, menu);
    _buttons.push_back(button);
    _entity_view_creator->createEntitySpriteView(button, layer + 1);
    _start_main_menu = button->getPressedPointer();

    button_string = std::make_shared<std::string>("return\nto menu");
    text_box = std::make_shared<TextBox>(
            TextBox({0, 0}, _camera, {0.5f, 0.25f}, button_string));
    button->addChild(text_box, button);
    _entity_view_creator->createEntityTextView(text_box);
}

void World::startGameOverMode() {
    _start_gameover = false;
    _gameover = true;
    _gameover_time_passed = 0;

    _bg_tiles.clear();
    spawnBgTiles(_camera->getPosition().y - _camera->getHeight(), false);
}

void World::updateGameOverMode(double t, float dt) {
    _camera->setPosition({_camera->getPosition().x, _player->getPosition().y});

    if (_gameover_time_passed < 2.f) {
        _gameover_time_passed += dt;
    } else {
        _gameover_time_passed = 0;
        _gameover = false;
        startGameoverOverlay();
    }

    spawnBgTiles(_camera->getPosition().y - _camera->getHeight(), false);
}

void World::startDebugMode() {
    _debug_mode = true;
    _doodle_mode = false;
    clear();

    // ui screen and background
    loadPauseOverlayButton();

    std::shared_ptr<UIEntity> background = std::make_shared<UIEntity>(
            UIEntity({0, 0}, _camera, {_camera->getWidth(), _camera->getHeight()}, _animation_players["background"],
                     {}, false));
    _ingame_ui_tree->addChild(background, _ingame_ui_tree);
    _entity_view_creator->createEntitySpriteView(background, 1);

    spawnPlayer({0, 2.5f});

    // portal radio music object
    _portal_radios.push_back(
            std::make_shared<PortalRadio>(
                    PortalRadio({0.5f, 2.5f}, _camera, {0.2f, 0.2f}, _animation_players["portal_radio"],
                                _audio_player)));
    _physics_entities.push_back(_portal_radios.back());
    _entity_view_creator->createEntitySpriteView(_portal_radios.back(), 4);
//    _entity_audio_creator->createEntityAudio(_portal_radios.back());

    // walls
    _walls.push_back(std::make_shared<Wall>(
            Wall({-0.5f, 0.f}, _camera, {1.f, 1.f}, _animation_players["wall"], {}, true)));
    _physics_entities.push_back(_walls.back());
    _entity_view_creator->createEntitySpriteView(_walls.back(), 3);

    _walls.push_back(std::make_shared<Wall>(
            Wall({0.5f, 0.f}, _camera, {1.f, 1.f}, _animation_players["wall"], {}, true)));
    _physics_entities.push_back(_walls.back());
    _entity_view_creator->createEntitySpriteView(_walls.back(), 3);

    std::shared_ptr<Enemy> enemy = std::make_shared<AdvancedEnemy>(
            AdvancedEnemy({0, 0}, _camera, {0.2f, 0.26f}, _animation_players["skeleton_red"]));
    _physics_entities.push_back(enemy);
    _bonuses.push_back(enemy);
    _enemies.push_back(enemy);
    _entity_view_creator->createEntitySpriteView(_bonuses.back(), 4);

    std::shared_ptr<HPBar> hp_bar = createHPBar(enemy, false, constants::hpbarhearts::entity_ui_size,
                                                {0, (enemy->getViewSize().y / 2) +
                                                    (constants::hpbarhearts::entity_ui_size.y / 2)});
    enemy->setHPBar(hp_bar);
    _ui_entities.push_back(hp_bar);

    _platforms.push_back(std::make_shared<Platform>(
            Platform({-0.5f, 1.f}, _camera, {0.4f, 0.1f}, _animation_players["green"])));
    _physics_entities.push_back(_platforms.back());
    _entity_view_creator->createEntitySpriteView(_platforms.back(), 3);

    // add bonus
    _platforms.back()->addBonus(_bonuses.back());
    _bonuses.back()->addObserver(_score);
}

void World::updateDebugMode(double t, float dt) {
    _camera->setPosition({_camera->getPosition().x, _player->getPosition().y});

    if (_input_map->f && _player->canShoot()) {
        _player->setCanShoot(false);
        spawnPlayerBullet(_player->getPosition(), true);
    }

    if (_input_map->k) {
        _start_gameover = true;
    }
}

void World::startDoodleMode() {
    _doodle_mode = true;
    _debug_mode = false;
    clear();

    // ui
    loadPauseOverlayButton();

    spawnPlayer();
    _player->addVelocity({0.f, _player->getInitialJumpVelocity() * 1.2f});

    doodleModeSpawnPlatforms();
    spawnBgTiles(_camera->getPosition().y + _camera->getHeight(), true);

    // score
    std::shared_ptr<std::string> text_box_string = std::make_shared<std::string>("score");
    std::shared_ptr<TextBox> score_text_box = std::make_shared<TextBox>(
            TextBox({0, (constants::camera_view_y_max / 2) - 0.25f}, _camera, {0.5f, 0.25f}, text_box_string));
    _score_text_box = score_text_box;
    _ingame_ui_tree->addChild(score_text_box, _ingame_ui_tree);
    _entity_view_creator->createEntityTextView(score_text_box);

    _player->addObserver(_score);
    _camera->addObserver(_score);
}

void World::updateDoodleMode(double t, float dt) {
    // camera movement
    if (_player->getPosition().y > _camera->getPosition().y + 0.4f) {
        _camera->setPosition({_camera->getPosition().x, _player->getPosition().y - 0.4f});
    }

    // score
    if (!_score_text_box.expired()) {
        std::shared_ptr<TextBox> score_text_box = _score_text_box.lock();
        score_text_box->setText("score\n" + std::to_string(_score->getScore()));
    }

    // game over
    if (_player->getCurrentHitPoints() == 0 ||
        _player->getPosition().y < _camera->getPosition().y - _camera->getHeight() / 2 - _player->getViewSize().y / 2) {
        _start_gameover = true;
    }

    // shooting
    if (_input_map->f && _player->canShoot()) {
        _player->setCanShoot(false);
        spawnPlayerBullet(_player->getPosition(), true);
    }

    doodleModeSpawnPlatforms();
    spawnBgTiles(_camera->getPosition().y + _camera->getHeight(), true);

    doodleModeDestroyPhysicsEntities();
}

void World::doodleModeSpawnPlatforms() {
    // todo: constants
    float y_distance = 0.7f;
    float platform_width = 0.4f;
    float platform_height = 0.075f;
    unsigned int platform_render_layer = 3;

    float y_spawn_pos = _camera->getPosition().y + (_camera->getHeight() / 2) * 1.1f;

    while (_last_platform_y_pos < y_spawn_pos) {
        float x_pos = Random::get_instance().uniform_real(-0.8, 0.8);
        _last_platform_y_pos += y_distance;

        float platform_type = Random::get_instance().uniform_real(0, 1);

        if (platform_type < 0.25f) {
            // static platform
            _platforms.push_back(std::make_shared<Platform>(
                    Platform({x_pos, _last_platform_y_pos}, _camera, {platform_width, platform_height},
                             _animation_players["green"])));

        } else if (platform_type < 0.40f) {
            // moving platform
            _platforms.push_back(std::make_shared<MovPlatform>(
                    MovPlatform({x_pos, _last_platform_y_pos}, _camera, {platform_width, platform_height}, true,
                                _animation_players["blue"])));

        } else if (platform_type < 0.55f) {
            _platforms.push_back(std::make_shared<MovPlatform>(
                    MovPlatform({x_pos, _last_platform_y_pos}, _camera, {platform_width, platform_height}, false,
                                _animation_players["yellow"])));

        } else if (platform_type < 0.70f) {
            // temporary platform
            _platforms.push_back(std::make_shared<TempPlatform>(
                    TempPlatform({x_pos, _last_platform_y_pos}, _camera, {platform_width, platform_height},
                                 _animation_players["white"])));

        } else if (platform_type < 0.85f) {
            // teleporting platform
            _platforms.push_back(std::make_shared<TelePlatform>(
                    TelePlatform({x_pos, _last_platform_y_pos}, _camera, {platform_width, platform_height}, true,
                                 _animation_players["blue_redsides"])));

        } else if (platform_type <= 1.f) {
            _platforms.push_back(std::make_shared<TelePlatform>(
                    TelePlatform({x_pos, _last_platform_y_pos}, _camera, {platform_width, platform_height}, false,
                                 _animation_players["yellow_redsides"])));
        }

        _physics_entities.push_back(_platforms.back());
        _entity_view_creator->createEntitySpriteView(_platforms.back(), platform_render_layer);

        // bonus
        float place_bonus = Random::get_instance().uniform_real(0, 1);

//        if (place_bonus < 0.1f) {
//            _bonuses.push_back(std::make_shared<SpringBonus>(
//                    SpringBonus({0, 0}, _camera, {0.2f, 0.2f}, _animation_players["spring"])));
//            _physics_entities.push_back(_bonuses.back());
//            _entity_view_creator->createEntitySpriteView(_bonuses.back(), 4);
//
//            // add bonus
//            _platforms.back()->addBonus(_bonuses.back());
//            _bonuses.back()->addObserver(_score);
//        } else if (place_bonus < 0.12f) {
//            _bonuses.push_back(std::make_shared<JetpackBonus>(
//                    JetpackBonus({0, 0}, _camera, {0.2f, 0.2f}, _animation_players["jetpack"])));
//            _physics_entities.push_back(_bonuses.back());
//            _entity_view_creator->createEntitySpriteView(_bonuses.back(), 4);
//
//            // add bonus
//            _platforms.back()->addBonus(_bonuses.back());
//            _bonuses.back()->addObserver(_score);
//        }

        if (place_bonus < 0.4f) {
            _bonuses.push_back(std::make_shared<SpikeBonus>(
                    SpikeBonus({0, 0}, _camera, {0.15f, 0.075f}, _animation_players["spikes"])));
            _physics_entities.push_back(_bonuses.back());
            _entity_view_creator->createEntitySpriteView(_bonuses.back(), 4);

            // add bonus
            _platforms.back()->addBonus(_bonuses.back());
            _bonuses.back()->addObserver(_score);
        } else if (place_bonus < 0.8f) {
            _bonuses.push_back(std::make_shared<HPBonus>(
                    HPBonus({0, 0}, _camera, {0.2f, 0.2f}, _animation_players["heart"])));
            _physics_entities.push_back(_bonuses.back());
            _entity_view_creator->createEntitySpriteView(_bonuses.back(), 4);

            // add bonus
            _platforms.back()->addBonus(_bonuses.back());
            _bonuses.back()->addObserver(_score);
        }
    }
}

//void World::doodleModeSpawnBgTiles() {
//    // todo: constant
//    unsigned int amount = 30;
//    float bg_tile_size = _camera->getWidth() / static_cast<float>(amount);
//
//    float y_spawn_pos = _camera->getPosition().y + (_camera->getHeight() / 2) * 1.1f;
//
//    while (_last_bg_tile_y_pos < y_spawn_pos) {
//        // floating precision errors
//        _last_bg_tile_y_pos += bg_tile_size - 0.001f;
//
//        float current_x_pos = constants::camera_view_x_min + bg_tile_size / 2;
//        for (unsigned int i = 0; i < amount; i++) {
//            _bg_tiles.push_back(std::make_shared<BgTile>(
//                    BgTile({current_x_pos, _last_bg_tile_y_pos}, _camera, {bg_tile_size, bg_tile_size},
//                           _animation_players["background_tile"])));
//            _ui_entities.push_back(_bg_tiles.back());
//            _entity_view_creator->createEntitySpriteView(_bg_tiles.back(), 1);
//
//            current_x_pos += bg_tile_size;
//        }
//    }
//}

void World::doodleModeDestroyPhysicsEntities() {
    // todo: constant
    float destroy_pos = _camera->getPosition().y - (_camera->getHeight() / 2) - 1.f;

    if (!_platforms.empty()) {
        while (_platforms.front()->getPosition().y < destroy_pos) {
            _platforms.erase(_platforms.begin());
        }
    }

    if (!_bg_tiles.empty()) {
        while (_bg_tiles.front()->getPosition().y < destroy_pos) {
            _bg_tiles.erase(_bg_tiles.begin());
        }
    }

    while (!_bonuses.empty() && _bonuses.front()->getPosition().y < destroy_pos) {
        _bonuses.erase(_bonuses.begin());
    }

    if (_active_bonus && !_active_bonus->isActive()) {
        _active_bonus = nullptr;
    }
}

void World::spawnPlayer(const Vector2f &spawn) {
    _player = std::make_shared<Doodle>(
            Doodle(spawn, _camera, constants::player::view_size, _input_map, _animation_players["adventurer"],
                   _audio_player));
    _physics_entities.push_back(_player);
    _entity_view_creator->createEntitySpriteView(_player, 5);
//    _entity_audio_creator->createEntityAudio(_player);

    // HP
    std::shared_ptr<HPBar> hp_bar = createHPBar(_player, true, constants::hpbarhearts::screen_ui_size);
    hp_bar->setPosition({-(_ingame_ui_tree->getViewSize().x / 2) + (hp_bar->getViewSize().x / 2),
                         -(_ingame_ui_tree->getViewSize().y / 2) + (hp_bar->getViewSize().y / 2)});
    _ingame_ui_tree->addChild(hp_bar, _ingame_ui_tree);
}

void World::spawnBgTiles(float y_spawn_position, bool up) {
    unsigned int amount = 30;
    float bg_tile_size = _camera->getWidth() / static_cast<float>(amount);

    while ((up && _last_bg_tile_y_pos < y_spawn_position) || (!up && _last_bg_tile_y_pos > y_spawn_position)) {
        // floating precision errors
        if (up) {
            _last_bg_tile_y_pos += bg_tile_size - 0.001f;
        } else {
            _last_bg_tile_y_pos -= bg_tile_size - 0.001f;
        }

        float current_x_pos = constants::camera_view_x_min + bg_tile_size / 2;
        for (unsigned int i = 0; i < amount; i++) {
            _bg_tiles.push_back(std::make_shared<BgTile>(
                    BgTile({current_x_pos, _last_bg_tile_y_pos}, _camera, {bg_tile_size, bg_tile_size},
                           _animation_players["background_tile"])));
            _ui_entities.push_back(_bg_tiles.back());
            _entity_view_creator->createEntitySpriteView(_bg_tiles.back(), 1);

            current_x_pos += bg_tile_size;
        }
    }
}

void World::spawnPlayerBullet(const Vector2f &position, bool up) {
    _player_bullets.push_back(
            std::make_shared<Bullet>(Bullet(position, _camera, {0.075f, 0.075f}, up, _animation_players["bullet"])));
    _physics_entities.push_back(_player_bullets.back());
    _entity_view_creator->createEntitySpriteView(_player_bullets.back(), 80);
}

void World::spawnEnemyBullet(const Vector2f &position, bool up) {
    _enemy_bullets.push_back(
            std::make_shared<Bullet>(Bullet(position, _camera, {0.075f, 0.075f}, up, _animation_players["bullet"])));
    _physics_entities.push_back(_enemy_bullets.back());
    _entity_view_creator->createEntitySpriteView(_enemy_bullets.back(), 80);
}

std::shared_ptr<HPBar> World::createHPBar(const std::weak_ptr<PhysicsEntity> &entity, bool left_alligned,
                                          const Vector2f &heart_size, const Vector2f &offset) {
    std::shared_ptr<HPBar> hp_bar = std::make_shared<HPBar>(
            HPBar({0, 0}, _camera, {0, 0}, _animation_players["heart"]));

    hp_bar->setHearts(entity, hp_bar, left_alligned, heart_size, offset);

    for (const auto &heart: hp_bar->getHearts()) {
        _entity_view_creator->createEntitySpriteView(heart, 200);
    }

    return hp_bar;
}

std::shared_ptr<UIEntity> World::craeteEmptyScreenUI() {
    return std::make_shared<UIEntity>(
            UIEntity({0, _camera->getPosition().y}, _camera, {_camera->getWidth(), _camera->getHeight()}, {}, {},
                     false));
}
