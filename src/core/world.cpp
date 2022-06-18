#include "world.h"

World::World() : _user_input_map(new InputMap) {

}

World::~World() = default;

void World::update(double t, float dt) {

}

std::shared_ptr<InputMap> World::getUserInputMap() {
    return _user_input_map;
}
