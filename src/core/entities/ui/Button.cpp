#include "Button.h"

#include <utility>

Button::Button(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize,
               AnimationPlayer animationPlayer, AudioPlayer audioPlayer, bool staticView)
        : UIWidget(position, std::move(camera), viewSize, std::move(animationPlayer), std::move(audioPlayer),
                   staticView), _pressed(false) {
    setHitbox(_position, _view_size);
}

bool Button::isPressed() const {
    return _pressed;
}

void Button::setPressed(bool pressed) {
    _pressed = pressed;
}

void Button::update(double t, float dt) {
    if (_pressed) {
        std::cout << "clicked button!" << std::endl;
        _pressed = false;
    }

    Entity::update(t, dt);
}
