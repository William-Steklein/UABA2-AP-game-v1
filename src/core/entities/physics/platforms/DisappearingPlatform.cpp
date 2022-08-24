#include "DisappearingPlatform.h"

#include <utility>

DisappearingPlatform::DisappearingPlatform(const Vector2f &position, std::shared_ptr<Camera> camera,
                                           const Vector2f &viewSize, AnimationPlayer animationPlayer,
                                           AudioPlayer audioPlayer, bool isStatic)
        : Platform(position, std::move(camera), viewSize, std::move(animationPlayer), std::move(audioPlayer),
                   isStatic) {

}

void DisappearingPlatform::update(double t, float dt) {
    std::cout << _collided << std::endl;
    if (_collided) {
        setHitbox({0, 0}, {0, 0});
        setViewSize({0, 0});
    }

    PhysicsEntity::update(t, dt);
}
