#include "Doodle.h"
#include <utility>

Doodle::Doodle(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize)
        : Entity(position, std::move(camera), viewSize) {

}

void Doodle::update(double t, float dt) {
    setScale({
                     std::sin(static_cast<float>(t)) + 1.5f,
                     std::sin(static_cast<float>(t)) + 1.5f,
             });

//    if (jump_condition) {
//        _position.y += 0.2;
//    }

    Entity::update(t, dt);
}

void Doodle::jump() {
    std::cout << "jumping" << std::endl;
    _position.y += 0.2;
}
