#ifndef GAMEENGINE_WORLD_H
#define GAMEENGINE_WORLD_H

#include "./utils/Stopwatch.h"
#include "utils/UserInputMap.h"
#include <memory>

namespace Core {
    class World {
    private:
        std::shared_ptr<UserInputMap> _user_input_map;
        bool _console_activated{false};

    public:
        World();
        ~World();

        void update(double t, float dt);

        std::shared_ptr<UserInputMap> getUserInputMap();

        std::string getConsoleText() const;
    };
}

#endif //GAMEENGINE_WORLD_H
