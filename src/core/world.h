#ifndef GAMEENGINE_WORLD_H
#define GAMEENGINE_WORLD_H

#include "stopwatch.h"
#include "input_map.h"
#include <memory>

class World {
private:
    std::shared_ptr<InputMap> _user_input_map;

public:
    World();

    ~World();

    void update(double t, float dt);

    std::shared_ptr<InputMap> getUserInputMap();
};

#endif //GAMEENGINE_WORLD_H
