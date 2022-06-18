#ifndef GAMEENGINE_I_SUBJECT_H
#define GAMEENGINE_I_SUBJECT_H

#include "i_observer.h"
#include <memory>
#include <set>

class ISubject {
private:
    std::set<std::shared_ptr<IObserver>> _observers;

public:
    void addObserver(const std::shared_ptr<IObserver> &observer);

    void removeObserver(const std::shared_ptr<IObserver> &observer);

    virtual void notifyObservers();

    virtual void notifyObservers(const std::string &event);
};

#endif // GAMEENGINE_I_SUBJECT_H
