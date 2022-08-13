#ifndef GAMEENGINE_IOBSERVER_H
#define GAMEENGINE_IOBSERVER_H

#include <string>

class IObserver {
public:
    virtual void handleEvent() = 0;

    virtual void handleEvent(const unsigned int &event, const unsigned int &channel) = 0;
};

#endif // GAMEENGINE_IOBSERVER_H
