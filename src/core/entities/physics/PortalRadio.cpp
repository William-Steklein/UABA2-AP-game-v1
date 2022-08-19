#include "PortalRadio.h"

PortalRadio::PortalRadio(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize,
                         AnimationPlayer animation_player, AudioPlayer audio_player, bool is_static)
        : PhysicsEntity(position, std::move(camera), viewSize, std::move(animation_player), std::move(audio_player),
                        is_static) {
    _hitbox->setSize({_view_size.x / 1.25f, _view_size.y / 1.75f});
    _hitbox->setOffset({0, _view_size.y * -0.2f});

    _mass = 1;

    setupPlayerPhysics(0.6, 1);

    // start music with loop
    playMusic("portal_radio", true, true);
    setAudioVolume(10);
}

void PortalRadio::update(double t, float dt) {
    // spatial audio test

    applySideScrolling();
    applyGravity();
    applyFriction();
    applyDrag();

    PhysicsEntity::update(t, dt);
}
