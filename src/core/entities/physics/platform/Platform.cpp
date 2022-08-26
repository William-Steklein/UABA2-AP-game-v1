#include "Platform.h"

#include <utility>

Platform::Platform(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize,
                   AnimationPlayer animationPlayer, AudioPlayer audioPlayer, bool isStatic)
        : PhysicsEntity(position, std::move(camera), viewSize, std::move(animationPlayer), std::move(audioPlayer),
                        isStatic), _bonus_y_offset(0) {
    _passthrough = true;
}

void Platform::addBonus(const std::weak_ptr<Bonus> &bonus) {
    _bonus = bonus;
    std::shared_ptr<Bonus> bonus_shared = _bonus.lock();
    _bonus_y_offset = bonus_shared->getViewSize().y / 2 + _view_size.y / 2;
}

void Platform::setPosition(const Vector2f &position) {
    if (!_bonus.expired()) {
        std::shared_ptr<Bonus> bonus = _bonus.lock();
        bonus->setPosition({position.x, position.y + _bonus_y_offset});
    }

    PhysicsEntity::setPosition(position);
}
