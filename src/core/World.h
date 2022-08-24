#ifndef GAMEENGINE_WORLD_H
#define GAMEENGINE_WORLD_H


#include <memory>
#include "Stopwatch.h"
#include "InputMap.h"
#include "Camera.h"
#include "entities/physics/Doodle.h"
#include "entities/IEntityViewCreator.h"
#include "entities/ui/UIWidget.h"
#include "entities/ui/Button.h"
#include "entities/IEntityViewCreator.h"
#include "entities/physics/Wall.h"
#include "entities/ui/TextBox.h"
#include "animation/Animation.h"
#include "constants/resources.h"
#include "entities/physics/PortalRadio.h"
#include "physics/Ray.h"
#include "audio/IEntityAudioCreator.h"
#include "entities/physics/platforms/Platform.h"
#include "entities/physics/platforms/MovPlatform.h"
#include "entities/physics/platforms/TelePlatform.h"
#include "entities/physics/platforms/DisappearingPlatform.h"
#include "Score.h"

class World {
private:
    std::shared_ptr<Camera> _camera;
    std::shared_ptr<InputMap> _input_map;

    // resource players
    std::map<std::string, AnimationPlayer> _animation_players;
    AudioPlayer _audio_player;

    // entities
    std::shared_ptr<IEntityViewCreator> _entity_view_creator;
    bool _force_static_view_update;
    std::shared_ptr<Doodle> _player;
    std::vector<std::shared_ptr<PortalRadio>> _portal_radios;

    std::vector<std::shared_ptr<Wall>> _walls;
    std::vector<std::shared_ptr<Platform>> _platforms;
    float last_y_pos_spawn = -0.75;

    std::vector<std::shared_ptr<UIWidget>> _ui_widget_entities;
    std::vector<std::shared_ptr<UIWidget>> _side_bars;
    std::vector<std::shared_ptr<Button>> _buttons;

    // score
    std::shared_ptr<Score> _score;

    // audio
    std::shared_ptr<IEntityAudioCreator> _entity_audio_creator;
    std::shared_ptr<Vector2f> _audio_listener_position;

    // game states
    std::shared_ptr<bool> _start_debug_mode;
    bool _debug_mode;
    std::shared_ptr<bool> _start_doodle_mode;
    bool _doodle_mode;

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

    // scenes
    void loadStartMenu();

    void startDebugMode();

    void startDoodleMode();

    void spawnPlayer();

    void spawnPlatforms();

    void destroyPlatforms();

    // update
    void updateUIEntities(double t, float dt);

    void updatePhysics(double t, float dt);

    void updatePhysicsEntities(double t, float dt);

    bool handleCollision(const std::shared_ptr<PhysicsEntity> &entity1, const std::shared_ptr<PhysicsEntity> &entity2,
                         bool resolve = true);

    bool handleCollision(const std::shared_ptr<Ray> &ray, const std::shared_ptr<PhysicsEntity> &entity,
                         bool set_collides = false);

    void handleUpdatePhysicsSpeed();

    void reset();
};


#endif //GAMEENGINE_WORLD_H
