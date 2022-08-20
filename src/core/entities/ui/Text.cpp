#include "Text.h"

Text::Text(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize,
           AnimationPlayer animationPlayer, AudioPlayer audioPlayer, bool staticView)
        : UIWidget(position, std::move(camera), viewSize, std::move(animationPlayer), std::move(audioPlayer),
                   staticView) {
    _hitbox = std::make_shared<Hitbox>(_position, _view_size);

}
