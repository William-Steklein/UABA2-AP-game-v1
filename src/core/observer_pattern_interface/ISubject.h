#ifndef GAMEENGINE_ISUBJECT_H
#define GAMEENGINE_ISUBJECT_H

#include "IObserver.h"
#include <memory>
#include <set>

namespace Core {
    class ISubject {
    private:
        std::set<std::shared_ptr<Core::IObserver>> _observers;

    public:
        void addObserver(const std::shared_ptr<Core::IObserver> &observer);

        void removeObserver(const std::shared_ptr<Core::IObserver> &observer);

        virtual void notifyObservers();

        virtual void notifyObservers(const std::string &event);
    };
}
#endif // GAMEENGINE_ISUBJECT_H
