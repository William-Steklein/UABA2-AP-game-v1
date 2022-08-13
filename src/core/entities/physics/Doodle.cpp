#include "Doodle.h"
#include <utility>

Doodle::Doodle(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize)
        : PhysicsEntity(position, std::move(camera), viewSize), _current_animation_frame(0),
          _current_animation_name(""), _prev_t(0), _facing_left(true) {
    _animations = {
            {"idle_standing_left",  {{0},                                0,     true}},
            {"idle_standing_right", {{1},                                0,     true}},
            {"idle_jumping_left",   {{2},                                0,     true}},
            {"idle_jumping_right",  {{3},                                0,     true}},
            {"explosion",           {{4, 5, 6, 7, 8, 9, 10, 11, 12, 13}, 0.25f, false}},
    };
}

void Doodle::update(double t, float dt) {
//    setScale({
//                     std::sin(static_cast<float>(t)) + 1.5f,
//                     std::sin(static_cast<float>(t)) + 1.5f,
//             });

    float wait_duration = 64 * dt * 4;
//    float wait_duration = 1;

    if (t - _prev_t >= (wait_duration)) {
        _prev_t = t;

        if (_facing_left) {
            _facing_left = false;
            startAnimation("explosion");
        } else {
            _facing_left = true;
            startAnimation("idle_standing_left");
        }
    }

    advanceAnimation();
    Entity::update(t, dt);
}

void Doodle::startAnimation(const std::string &animation_name) {
    _current_animation_name = animation_name;
    _current_animation_frame = -1;
    _current_animation_time = -(_animations.at(_current_animation_name).getFramerate());
}

void Doodle::advanceAnimation() {
    if (_current_animation_name.empty()) {
        return;
    }

    std::vector<unsigned int> texture_frames = _animations.at(_current_animation_name).getTextureFrames();
    float framerate = _animations.at(_current_animation_name).getFramerate();
    _current_animation_time += framerate;

    if (_current_animation_frame + 1 < texture_frames.size() && (_current_animation_time >= 1 || framerate == 0)) {
        notifyObservers(texture_frames[_current_animation_frame + 1], 0);
        _current_animation_frame += 1;
        _current_animation_time -= 1;
    }
}
