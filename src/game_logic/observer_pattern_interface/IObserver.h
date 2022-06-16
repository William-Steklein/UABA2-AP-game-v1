#ifndef GAMEENGINE_IOBSERVER_H
#define GAMEENGINE_IOBSERVER_H

#include <string>

namespace Core {
    class IObserver {
    public:
        virtual void handleEvent() = 0;

        virtual void handleEvent(const std::string &event) = 0;
    };
} // namespace Core

#endif // GAMEENGINE_IOBSERVER_H
