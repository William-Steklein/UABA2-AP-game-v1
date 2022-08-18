#include "UIWidget.h"

UIWidget::UIWidget(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &view_size,
                   AnimationPlayer animation_player, AudioPlayer audio_player, bool static_view)
        : Entity(position, std::move(camera), view_size, std::move(animation_player), std::move(audio_player)),
          _static_view(static_view) {

}

bool UIWidget::is_static_view() const {
    return _static_view;
}
