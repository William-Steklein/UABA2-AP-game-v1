#ifndef GAMEENGINE_WORLD_H
#define GAMEENGINE_WORLD_H


#include <memory>
#include "Stopwatch.h"
#include "InputMap.h"
#include "Camera.h"
#include "entities/physics/Doodle.h"
#include "entities/IEntityViewCreator.h"
#include "entities/ui/UIWidget.h"
#include "entities/IEntityViewCreator.h"
#include "entities/physics/Wall.h"
#include "animation/AnimationPlayer.h"
#include "constants/resources.h"
#include "entities/physics/PortalRadio.h"
#include "physics/Ray.h"

class World {
private:
    std::shared_ptr<Camera> _camera;
    std::shared_ptr<InputMap> _input_map;

    // resources
    std::map<std::string, std::shared_ptr<std::map<std::string, AnimationPlayer>>> _animation_groups;

    // entities
    std::shared_ptr<IEntityViewCreator> _entity_view_creator;
    bool _force_static_update;
    std::shared_ptr<Doodle> _player;
    std::vector<std::shared_ptr<Wall>> _walls;
    std::vector<std::shared_ptr<PortalRadio>> _portal_radios;

    std::vector<std::shared_ptr<UIWidget>> _ui_widget_entities;
    std::vector<std::shared_ptr<UIWidget>> _side_bars;

public:
    World(std::shared_ptr<IEntityViewCreator> entity_view_creator, float x_min, float x_max, float y_min, float y_max);

    ~World();

    static void sleep();

    void update();

    void updateScreenResolution(float x_min, float x_max, float y_min, float y_max);

    std::shared_ptr<InputMap> getUserInputMap();

private:
    void loadResources();

    void loadAnimations();

    void loadAudio();

    void initializeUIWidgets();

    void updateSidebars();

    void initializePhysicsEntities();

    void updateUIEntities(double t, float dt);

    void updatePhysics(double t, float dt);

    void updatePhysicsEntities(double t, float dt);

    bool handleCollision(const std::shared_ptr<PhysicsEntity> &entity1, const std::shared_ptr<PhysicsEntity> &entity2,
                         bool resolve = true);

    bool handleCollision(const std::shared_ptr<Ray> &ray, const std::shared_ptr<PhysicsEntity> &entity);
};


#endif //GAMEENGINE_WORLD_H
