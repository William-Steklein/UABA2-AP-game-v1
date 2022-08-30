#include "Random.h"

Random::Random() : generator(device()) {

}

Random &Random::get_instance() {
    static Random instance;
    return instance;
}

int Random::uniform_int(int a, int b) {
    std::uniform_int_distribution<int> d(a, b);
    return d(generator);
}

float Random::uniform_real(float a, float b) {
    std::uniform_real_distribution<float> d(a, b);
    return d(generator);
}

int Random::bernoulli(float p) {
    std::bernoulli_distribution d(p);
    return d(generator);
}

float Random::normal(float m, float n) {
    std::normal_distribution<float> d(m, n);
    return d(generator);
}
