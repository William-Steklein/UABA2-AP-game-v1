#ifndef GAMEENGINE_STOPWATCH_H
#define GAMEENGINE_STOPWATCH_H

#include <chrono>
#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <thread>

class Stopwatch {
    std::chrono::steady_clock::time_point _a;
    std::chrono::steady_clock::time_point _b;
    unsigned int _fps_limit;
    float _ms_limit;
    bool _cap_framerate;

    float _delta_time;
    float _physics_delta_time;
    double _physics_time;
    float _accumulator;
    float _physics_speed;

    float _sample_duration;
    float _duration;
    float _frame_count;
    float _average_fps;

public:
    Stopwatch();

    Stopwatch(const Stopwatch &) = delete;

    Stopwatch &operator=(const Stopwatch &) = delete;

    static Stopwatch &getInstance();

    void sleep_frame();

    float getDeltaTime() const;

    float getPhysicsDeltaTime() const;

    void setPhysicsDeltaTime(float dt);

    double getPhysicsTime() const;

    float getPhysicsSpeed() const;

    void setPhysicsSpeed(float physics_speed);

    void PhysicsUpdate(const std::function<void(double, float)> &func);

    float computeAlpha() const;

    bool getCapFramerate() const;

    void setCapFramerate(bool cap_fps);

    unsigned int getFpsLimit() const;

    void setFpsLimit(unsigned int fps_limit);

    float getAverageFps() const;
};

#endif // GAMEENGINE_STOPWATCH_H
