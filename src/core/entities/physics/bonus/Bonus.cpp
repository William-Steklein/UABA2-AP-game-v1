#include "Bonus.h"

Bonus::Bonus(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize,
             AnimationPlayer animationPlayer, AudioPlayer audioPlayer, bool isStatic)
        : PhysicsEntity(position, std::move(camera), viewSize, std::move(animationPlayer), std::move(audioPlayer),
                        isStatic) {

}

void Bonus::update(double t, float dt) {
    if (_collided) {
        disappear();
    }

    PhysicsEntity::update(t, dt);
}
