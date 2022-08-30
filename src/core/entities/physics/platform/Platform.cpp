#include "Platform.h"

#include <utility>

Platform::Platform(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize,
                   AnimationPlayer animationPlayer, AudioPlayer audioPlayer, bool isStatic)
        : PhysicsEntity(position, std::move(camera), viewSize, std::move(animationPlayer), std::move(audioPlayer),
                        isStatic), _bonus_offset({0, 0}) {
    _passthrough = true;
}

void Platform::addBonus(const std::weak_ptr<Bonus> &bonus) {
    _bonus = bonus;
    std::shared_ptr<Bonus> bonus_shared = _bonus.lock();
    float x_rand = Random::get_instance().uniform_real(-(_hitbox->getSize().x / 2 - bonus_shared->getViewSize().x / 2),
                                                       _hitbox->getSize().x / 2 - bonus_shared->getViewSize().x / 2);
    _bonus_offset = {x_rand, bonus_shared->getViewSize().y / 2 + _view_size.y / 2};
    setPosition(_position);
}

void Platform::setPosition(const Vector2f &position) {
    if (!_bonus.expired()) {
        std::shared_ptr<Bonus> bonus = _bonus.lock();
        bonus->setPosition(position + _bonus_offset);
    }

    PhysicsEntity::setPosition(position);
}
