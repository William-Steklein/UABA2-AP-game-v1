#include "ISubject.h"

void ISubject::addObserver(const std::shared_ptr<IObserver> &observer) { _observers.insert(observer); }

void ISubject::removeObserver(const std::shared_ptr<IObserver> &observer) { _observers.erase(observer); }

void ISubject::notifyObservers() {
    for (const auto &observer: _observers) {
        observer->handleEvent();
    }
}

void ISubject::notifyObservers(const std::string &event, const std::string& channel) {
    for (const auto &observer: _observers) {
        observer->handleEvent(event, channel);
    }
}
