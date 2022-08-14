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
#include "animation/Animation.h"
#include "constants/animation_data.h"

class World {
private:
    std::shared_ptr<Camera> _camera;
    std::shared_ptr<IEntityViewCreator> _entity_view_creator;
    std::map<std::string, std::shared_ptr<std::map<std::string, Animation>>> _animation_groups;
    bool _force_static_update;

    std::vector<std::shared_ptr<UIWidget>> _ui_widget_entities;

    std::shared_ptr<Doodle> _player;
    std::vector<std::shared_ptr<Wall>> _walls;
    //std::vector<std::shared_ptr<Platform>> _platforms;
    //std::vector<std::shared_ptr<BackgroundTile>> _background_tiles;
    //std::vector<std::shared_ptr<Bonus>> _bonuses;
    //std::vector<std::shared_ptr<Enemy>> _enemies;

    std::shared_ptr<InputMap> _user_input_map;

public:
    World(std::shared_ptr<IEntityViewCreator> entity_view_creator, float x_min, float x_max, float y_min, float y_max);

    ~World();

    static void sleep();

    void update();

    void updateScreenResolution(float x_min, float x_max, float y_min, float y_max);

    std::shared_ptr<InputMap> getUserInputMap();

private:
    void loadAnimations();

    void initializeEntities();

    void initializeUIWidgets();

    void initializeDoodle();

    void updateUIEntities(double t, float dt);

    void updatePhysics(double t, float dt);

    void updatePhysicsEntities(double t, float dt);

    bool handleCollision(const std::shared_ptr<PhysicsEntity> &entity1, const std::shared_ptr<PhysicsEntity> &entity2,
                         bool resolve = true);
};


#endif //GAMEENGINE_WORLD_H
