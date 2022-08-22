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
#include "entities/physics/Platform.h"

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

    std::vector<std::shared_ptr<UIWidget>> _ui_widget_entities;
    std::vector<std::shared_ptr<UIWidget>> _side_bars;
    std::vector<std::shared_ptr<Button>> _buttons;

    // audio
    std::shared_ptr<IEntityAudioCreator> _entity_audio_creator;
    std::shared_ptr<Vector2f> _audio_listener_position;

    // flow
    std::shared_ptr<bool> _start_game;

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

    void resetEntities();

    void initializeSideBars();

    void updateSidebars();

    // scenes
    void initializeStartMenu();

    void initializePhysicsEntities();

    void updateUIEntities(double t, float dt);

    void updatePhysics(double t, float dt);

    void updatePhysicsEntities(double t, float dt);

    bool handleCollision(const std::shared_ptr<PhysicsEntity> &entity1, const std::shared_ptr<PhysicsEntity> &entity2,
                         bool resolve = true);

    bool handleCollision(const std::shared_ptr<Ray> &ray, const std::shared_ptr<PhysicsEntity> &entity);
};


#endif //GAMEENGINE_WORLD_H
