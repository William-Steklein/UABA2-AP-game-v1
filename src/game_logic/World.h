#ifndef GAMEENGINE_WORLD_H
#define GAMEENGINE_WORLD_H

#include "./utils/Stopwatch.h"
#include "utils/UserInputMap.h"
#include "EventManager.h"
#include <memory>

namespace Core {
    class World {
    private:
        std::shared_ptr<UserInputMap> _user_input_map;
        bool _console_activated{false};
        std::shared_ptr<EventManager> _event_manager;

    public:
        World();
        ~World();

        void update(double t, float dt);

        void assignEvents();

        std::shared_ptr<UserInputMap> getUserInputMap();

        std::string getConsoleText() const;
    };
}

#endif //GAMEENGINE_WORLD_H
