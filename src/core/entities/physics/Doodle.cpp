#include "Doodle.h"
#include <utility>

Doodle::Doodle(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize,
               std::shared_ptr<std::map<std::string, Animation>> animation_group)
        : PhysicsEntity(position, std::move(camera), viewSize, std::move(animation_group)), _prev_t(0),
          _facing_left(true), _current_animation(1) {

    startAnimation("crouch", _facing_left);
    std::cout << 0 << std::endl;
}

void Doodle::update(double t, float dt) {
//    float wait_duration = 64 * dt * 4;
    float wait_duration = 3;

    if (t - _prev_t >= (wait_duration)) {
        _prev_t = t;

        std::cout << _current_animation << std::endl;

        switch (_current_animation) {
            case 0:
                startAnimation("crouch", _facing_left);
                break;
            case 1:
                startAnimation("fall", _facing_left);
                break;
            case 2:
                startAnimation("idle", _facing_left);
                break;
            case 3:
                startAnimation("jump", _facing_left);
                break;
            case 4:
                startAnimation("run", _facing_left);
                _current_animation = -1;
                break;
            default:
                _current_animation = -1;
                break;
        }
        _current_animation++;
    }

    Entity::update(t, dt);
}
