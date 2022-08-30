#include "Button.h"

#include <utility>

Button::Button(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize,
               AnimationPlayer animationPlayer, AudioPlayer audioPlayer, bool staticView)
        : UIEntity(position, std::move(camera), viewSize, std::move(animationPlayer), std::move(audioPlayer),
                   staticView), _pressed_button(false), _pressed(std::make_shared<bool>(false)) {
    setHitbox(_position, _view_size);
}

bool Button::isPressed() const {
    return _pressed_button;
}

void Button::setPressed(bool pressed) {
    _pressed_button = pressed;
    *_pressed = pressed;
}

void Button::update(double t, float dt) {
    if (_pressed_button) {
//        std::cout << "clicked button!" << std::endl;
        _pressed_button = false;
    }

    UIEntity::update(t, dt);
}

std::shared_ptr<bool> Button::getPressedPointer() {
    return _pressed;
}
