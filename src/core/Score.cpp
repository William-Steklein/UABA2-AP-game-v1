#include "Score.h"

Score::Score() : _score(0) {

}

void Score::handleEvent() {

}

void Score::handleEvent(const unsigned int &event, const unsigned int &channel) {
    if (channel == 25) {
        addScore(event);
    } else if (channel == 26) {
        substractScore(event);
    }
}

void Score::addScore(unsigned int score_amount) {
    _score += score_amount;
}

void Score::substractScore(unsigned int score_amount) {
    if (score_amount <= _score) {
        _score -= score_amount;
    } else {
        _score = 0;
    }
}

unsigned int Score::getScore() const {
    return _score;
}

void Score::reset() {
    _score = 0;
}
