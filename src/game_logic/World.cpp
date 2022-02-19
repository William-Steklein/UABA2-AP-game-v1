#include "World.h"

Core::World::World() : _user_input_map(new UserInputMap), _event_manager(new EventManager) {
    assignEvents();
}

Core::World::~World() = default;

void Core::World::update(double t, float dt) {
    // go into console
    if (_user_input_map->slash && !_console_activated) {
        _console_activated = true;
        _user_input_map->get_user_input_stream = true;
        _event_manager->fireEvent("testevent");
        std::cout << "In console!" << std::endl;
    }

    // go out of console
    if (_console_activated && _user_input_map->esc) {
        std::cout << "Out of console!" << std::endl;
        _console_activated = false;
        _user_input_map->get_user_input_stream = false;
    }
}

void Core::World::assignEvents() {
    _event_manager->registerEvent("testevent", [=]{
        std::cout << "test" << std::endl;
    });
}

std::shared_ptr<Core::UserInputMap> Core::World::getUserInputMap() {
    return _user_input_map;
}

std::string Core::World::getConsoleText() const {
    return _user_input_map->user_input_stream;
}
