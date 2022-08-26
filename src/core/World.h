#ifndef GAMEENGINE_WORLD_H
#define GAMEENGINE_WORLD_H


#include <memory>

#include "Stopwatch.h"
#include "Random.h"
#include "Camera.h"
#include "InputMap.h"
#include "Score.h"

#include "physics/Ray.h"
#include "physics/collisions.h"

#include "entities/IEntityViewCreator.h"
#include "entities/physics/Doodle.h"
#include "entities/physics/Wall.h"
#include "entities/physics/platform/Platform.h"
#include "entities/physics/platform/MovPlatform.h"
#include "entities/physics/platform/TelePlatform.h"
#include "entities/physics/platform/TempPlatform.h"
#include "entities/physics/PortalRadio.h"

#include "entities/ui/UIEntity.h"
#include "entities/ui/BgTile.h"
#include "entities/ui/Button.h"
#include "entities/ui/TextBox.h"

#include "constants/resources.h"
#include "animation/Animation.h"
#include "audio/IEntityAudioCreator.h"

class World {
private:
    std::shared_ptr<Camera> _camera;
    std::shared_ptr<InputMap> _input_map;
    std::shared_ptr<Score> _score;

    // game states
    std::shared_ptr<bool> _start_debug_mode;
    bool _debug_mode;
    std::shared_ptr<bool> _start_doodle_mode;
    bool _doodle_mode;

    // entities
    std::shared_ptr<IEntityViewCreator> _entity_view_creator;
    bool _force_static_view_update;

    std::vector<std::weak_ptr<PhysicsEntity>> _physics_entities;
    std::shared_ptr<Doodle> _player;
    std::vector<std::shared_ptr<Wall>> _walls;
    std::vector<std::shared_ptr<Platform>> _platforms;
    float _last_platform_y_pos;
    std::vector<std::shared_ptr<PortalRadio>> _portal_radios;

    std::vector<std::weak_ptr<UIEntity>> _ui_entities;
    std::vector<std::shared_ptr<UIEntity>> _static_ui;
    std::vector<std::shared_ptr<UIEntity>> _side_bars;
    std::vector<std::shared_ptr<BgTile>> _bg_tiles;
    float _last_bg_tile_y_pos;
    std::shared_ptr<TextBox> _score_text_box;
    std::vector<std::shared_ptr<Button>> _buttons;

    // resource players
    std::map<std::string, AnimationPlayer> _animation_players;
    AudioPlayer _audio_player;

    // audio
    std::shared_ptr<IEntityAudioCreator> _entity_audio_creator;
    std::shared_ptr<Vector2f> _audio_listener_position;

public:
    World(float x_min, float x_max, float y_min, float y_max, std::shared_ptr<IEntityViewCreator> entity_view_creator,
          std::shared_ptr<IEntityAudioCreator> entity_audio_creator);

    ~World();

    static void sleep();

    void update();

    void updateScreenResolution(float x_min, float x_max, float y_min, float y_max);

    void updateMousePosition(float x, float y);

    std::shared_ptr<InputMap> getUserInputMap();

private:
    void loadResources();

    void loadTextures();

    void loadAnimations();

    void loadAudio();

    void initializeSideBars();

    void updateSidebars();

    // update
    void gameUpdate(double t, float dt);

    void updateUIEntities(double t, float dt);

    void physicsUpdate(double t, float dt);

    void updatePhysicsEntities(double t, float dt);

    void updatePhysicsCollisions();

    void handleUpdatePhysicsSpeed();

    void clear();

    // scenes
    void loadStartMenu();

    void startDebugMode();

    void updateDebugMode(double t, float dt);

    void startDoodleMode();

    void updateDoodleMode(double t, float dt);

    void spawnPlayer(const Vector2f &spawn = constants::player::spawn_position);

    float getSpawnPosY();

    float getDestroyPosY();

    void spawnPlatforms();

    void destroyPlatforms();

    void spawnBgTiles();

    void destroyBgTiles();
};


#endif //GAMEENGINE_WORLD_H
