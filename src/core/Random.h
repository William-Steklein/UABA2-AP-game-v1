#ifndef GAMEENGINE_RANDOM_H
#define GAMEENGINE_RANDOM_H


#include <random>

class Random {
private:
    std::random_device device;
    std::mt19937 generator;

    Random();

public:
    Random(const Random &) = delete;

    Random &operator=(const Random &) = delete;

    static Random &get_instance();

    int uniform_int(int a, int b);

    float uniform_real(float a, float b);

    int bernoulli(float p);

    float normal(float m, float n);
};


#endif //GAMEENGINE_RANDOM_H
