#ifndef GAMEENGINE_EVENTMANAGER_H
#define GAMEENGINE_EVENTMANAGER_H

#include <map>
#include <string>
#include <functional>
#include <list>

namespace Core {
    class EventManager {
    private:
        std::map<std::string, std::list<std::function<void()>>> events;

    public:
        void registerEvent(const std::string& event_name, const std::function<void()>& func);
        void fireEvent(const std::string& event_name);
    };
}

#endif //GAMEENGINE_EVENTMANAGER_H
