#include "EventManager.h"

void Core::EventManager::registerEvent(const std::string& event_name, const std::function<void()>& func) {
    if (!events.contains(event_name))
        events[event_name] = {func};
    else
        events[event_name].push_back(func);
}

void Core::EventManager::fireEvent(const std::string& event_name) {
    for (const auto& func : events[event_name]) {
        func();
    }
}
