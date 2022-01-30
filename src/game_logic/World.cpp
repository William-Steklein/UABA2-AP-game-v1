#include "World.h"

Core::World::World() : _user_input_map(new UserInputMap) {
}

Core::World::~World() = default;

void Core::World::update(double t, float dt) {
    // go into console
    if (_user_input_map->slash && !_console_activated) {
        _console_activated = true;
        _user_input_map->get_user_input_stream = true;
        std::cout << "In console!" << std::endl;
    }

    // go out of console
    if (_console_activated && _user_input_map->esc) {
        std::cout << "Out of console!" << std::endl;
        _console_activated = false;
        _user_input_map->get_user_input_stream = false;
    }
}

std::shared_ptr<Core::UserInputMap> Core::World::getUserInputMap() {
    return _user_input_map;
}

std::string Core::World::getConsoleText() const {
    return _user_input_map->user_input_stream;
}
