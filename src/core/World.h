#ifndef GAMEENGINE_WORLD_H
#define GAMEENGINE_WORLD_H


#include "Stopwatch.h"
#include "InputMap.h"
#include "Camera.h"
#include <memory>
#include "entities/Doodle.h"
#include "entities/IEntityViewCreator.h"

class World {
private:

    std::shared_ptr<Doodle> _player;
    //std::vector<std::shared_ptr<Platform>> _platforms;
    //std::vector<std::shared_ptr<BackgroundTile>> _background_tiles;
    //std::vector<std::shared_ptr<Bonus>> _bonuses;
    //std::vector<std::shared_ptr<Monster>> _monsters;

    std::shared_ptr<Camera> _camera;
    std::shared_ptr<IEntityViewCreator> _entity_view_creator;

    std::shared_ptr<InputMap> _user_input_map;

public:
    World(std::shared_ptr<IEntityViewCreator> entity_view_creator, float x_min, float x_max, float y_min, float y_max);

    ~World();

    static void sleep();

    void update();

    std::shared_ptr<InputMap> getUserInputMap();

private:
    void initializeEntities();

    void initializeDoodle();

    void update(double t, float dt);

    void updateEntities(double t, float dt);
};

#endif //GAMEENGINE_WORLD_H
