#include "Stopwatch.h"

#ifdef WIN32

#include <windows.h>

void timerSleep(double seconds) {
    using namespace std::chrono;

    static HANDLE timer = CreateWaitableTimer(nullptr, FALSE, nullptr);
    static double estimate = 5e-3;
    static double mean = 5e-3;
    static double m2 = 0;
    static int64_t count = 1;

    while (seconds - estimate > 1e-7) {
        double toWait = seconds - estimate;
        LARGE_INTEGER due;
        due.QuadPart = -int64_t(toWait * 1e7);
        auto start = high_resolution_clock::now();
        SetWaitableTimerEx(timer, &due, 0, nullptr, nullptr, nullptr, 0);
        WaitForSingleObject(timer, INFINITE);
        auto end = high_resolution_clock::now();

        double observed = static_cast<double>((end - start).count()) / 1e9;
        seconds -= observed;

        ++count;
        double error = observed - toWait;
        double delta = error - mean;
        mean += delta / static_cast<double>(count);
        m2 += delta * (error - mean);
        double stddev = sqrt(m2 / static_cast<double>((count - 1)));
        estimate = mean + stddev;
    }

    // spin lock
    auto start = high_resolution_clock::now();
    while (static_cast<double>((high_resolution_clock::now() - start).count()) / 1e9 < seconds);
}

#endif

Stopwatch::Stopwatch()
        : _a(std::chrono::steady_clock::now()), _b(std::chrono::steady_clock::now()), _fps_limit(60),
          _cap_framerate(true),
          _delta_time(0), _physics_delta_time(1.0f / 60), _physics_time(0), _accumulator(0), _physics_speed(1),
          _sample_duration(500), _duration(0), _frame_count(0), _average_fps(0) {
    _ms_limit = (1000.f / static_cast<float>(_fps_limit));
}

Stopwatch &Stopwatch::getInstance() {
    static Stopwatch instance;
    return instance;
}

void Stopwatch::sleep_frame() {
    _a = std::chrono::steady_clock::now();
    std::chrono::duration<float> work_time = _a - _b;

    if (_cap_framerate & (work_time.count() * 1e3 < _ms_limit)) {
        std::chrono::duration<float> delta_us((_ms_limit / 1e3) - work_time.count());

#ifdef WIN32
        timerSleep(delta_us.count());
#else
        std::this_thread::sleep_for(
                std::chrono::microseconds(std::chrono::duration_cast<std::chrono::microseconds>(delta_us)));
#endif
    }

    _b = std::chrono::steady_clock::now();
    std::chrono::duration<float> sleep_time = _b - _a;

    // frame counter
    _frame_count++;
    _delta_time = (work_time + sleep_time).count() * 1e3f;
    _duration += _delta_time;

    if (_duration >= _sample_duration) {
        _average_fps = _frame_count / _duration * 1e3f;

        _frame_count = 0;
        _duration = 0;
    }
}

float Stopwatch::getDeltaTime() const { return _delta_time * 1e-3f; }

float Stopwatch::getPhysicsDeltaTime() const { return _physics_delta_time; }

void Stopwatch::setPhysicsDeltaTime(float dt) { _physics_delta_time = dt; }

double Stopwatch::getPhysicsTime() const { return _physics_time; }

void Stopwatch::increasePhysicsTime() { _physics_time += _physics_delta_time; }

float Stopwatch::getPhysicsSpeed() const { return _physics_speed; }

void Stopwatch::setPhysicsSpeed(float physics_speed) { _physics_speed = physics_speed; }

float Stopwatch::getAccumulator() const { return _accumulator; }

void Stopwatch::increaseAccumulator() { _accumulator += _delta_time * 1e-3f * _physics_speed; }

void Stopwatch::decreaseAccumulator() { _accumulator -= _physics_delta_time; }

float Stopwatch::computeAlpha() const { return _accumulator / _physics_delta_time; }

bool Stopwatch::getCapFramerate() const { return _cap_framerate; }

void Stopwatch::setCapFramerate(bool cap_fps) { _cap_framerate = cap_fps; }

unsigned int Stopwatch::getFpsLimit() const { return _fps_limit; }

void Stopwatch::setFpsLimit(unsigned int fps_limit) {
    _fps_limit = fps_limit;
    _ms_limit = (1e3f / static_cast<float>(_fps_limit));
}

float Stopwatch::getAverageFps() const { return _average_fps; }