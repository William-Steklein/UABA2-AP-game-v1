#include "PortalRadio.h"

#include <utility>

PortalRadio::PortalRadio(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize,
                         std::shared_ptr<std::map<std::string, AnimationPlayer>> animationGroup, bool isStatic)
        : PhysicsEntity(position, std::move(camera), viewSize, std::move(animationGroup), isStatic) {
    _hitbox->setSize({_view_size.x / 1.25f, _view_size.y / 1.75f});
    _hitbox->setOffset({0, _view_size.y * -0.2f});

    _mass = 1;

    setupPlayerPhysics(0.6, 1);

    // start music with loop


}

void PortalRadio::update(double t, float dt) {
    // spatial audio test

    applySideScrolling();
    applyGravity();
    applyFrictionAndDrag();

    PhysicsEntity::update(t, dt);
}
