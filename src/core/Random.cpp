#include "Random.h"

Random::Random() : generator(device()) {

}

Random &Random::get_instance() {
    static Random instance;
    return instance;
}

int Random::uniform_int(int a, int b) {
    std::uniform_int_distribution<int> distribution(a, b);
    return distribution(generator);
}

float Random::uniform_real(float a, float b) {
    std::uniform_real_distribution<float> distribution(a, b);
    return distribution(generator);
}

int Random::bernoulli(float p) {
    std::bernoulli_distribution distribution(p);
    return distribution(generator);
}

float Random::normal(float m, float n) {
    std::normal_distribution<float> distribution(m, n);
    return distribution(generator);
}
