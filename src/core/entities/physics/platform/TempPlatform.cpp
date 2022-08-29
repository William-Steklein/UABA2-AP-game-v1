#include "TempPlatform.h"

#include <utility>

TempPlatform::TempPlatform(const Vector2f &position, std::shared_ptr<Camera> camera,
                           const Vector2f &viewSize, AnimationPlayer animationPlayer,
                           AudioPlayer audioPlayer, bool isStatic)
        : Platform(position, std::move(camera), viewSize, std::move(animationPlayer), std::move(audioPlayer),
                   isStatic) {

}

void TempPlatform::update(double t, float dt) {
    if (_collided) {
        disappear();
        if (!_bonus.expired()) {
            std::shared_ptr<Bonus> bonus = _bonus.lock();
            bonus->disappear();
        }
    }

    PhysicsEntity::update(t, dt);
}
