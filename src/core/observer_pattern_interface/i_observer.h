#ifndef GAMEENGINE_I_OBSERVER_H
#define GAMEENGINE_I_OBSERVER_H

#include <string>

class IObserver {
public:
    virtual void handleEvent() = 0;

    virtual void handleEvent(const std::string &event) = 0;
};

#endif // GAMEENGINE_I_OBSERVER_H
