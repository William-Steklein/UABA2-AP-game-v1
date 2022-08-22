#include "TextBox.h"

TextBox::TextBox(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize,
                 std::shared_ptr<std::string> text, AnimationPlayer animationPlayer, AudioPlayer audioPlayer,
                 bool staticView)
        : UIWidget(position, std::move(camera), viewSize, std::move(animationPlayer), std::move(audioPlayer),
                   staticView), _text(std::move(text)) {
    _hitbox = std::make_shared<Hitbox>(_position, _view_size);

}

std::shared_ptr<std::string> TextBox::getText() {
    return _text;
}
