#include "Doodle.h"
#include <utility>

Doodle::Doodle(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize)
        : PhysicsEntity(position, std::move(camera), viewSize), _prev_t(0), _facing_left(true) {

}

void Doodle::update(double t, float dt) {
//    setScale({
//                     std::sin(static_cast<float>(t)) + 1.5f,
//                     std::sin(static_cast<float>(t)) + 1.5f,
//             });

//    std::cout << "time: " << t << std::endl;
//    std::cout << "delta time: " << dt << std::endl;


    if (t - _prev_t >= (8 * dt * 4 + dt)) {
        _prev_t = t;
        if (_facing_left) {
            _facing_left = false;
            notifyObservers("explosion", "animation");
        } else {
            _facing_left = true;
            notifyObservers("idle_left", "animation");
        }
    }

//    std::cout << _position << std::endl;

    Entity::update(t, dt);
}
