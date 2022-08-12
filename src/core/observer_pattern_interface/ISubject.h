#ifndef GAMEENGINE_ISUBJECT_H
#define GAMEENGINE_ISUBJECT_H

#include "IObserver.h"
#include <memory>
#include <set>

class ISubject {
private:
    std::set<std::shared_ptr<IObserver>> _observers;

public:
    void addObserver(const std::shared_ptr<IObserver> &observer);

    void removeObserver(const std::shared_ptr<IObserver> &observer);

    virtual void notifyObservers();

    virtual void notifyObservers(const std::string &event, const std::string& channel="");
};

#endif // GAMEENGINE_ISUBJECT_H
