#ifndef GAMEENGINE_SCORE_H
#define GAMEENGINE_SCORE_H


#include <iostream>
#include "observer-pattern-interface/IObserver.h"

class Score : public IObserver {
private:
    unsigned int _score;

public:
    Score();

    void handleEvent() override;

    void handleEvent(const unsigned int &event, const unsigned int &channel) override;

    void addScore(unsigned int score_amount);

    void substractScore(unsigned int score_amount);

    unsigned int getScore() const;

    void reset();
};


#endif //GAMEENGINE_SCORE_H
