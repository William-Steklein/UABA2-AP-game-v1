#include "UIWidget.h"

UIWidget::UIWidget(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize,
                   std::shared_ptr<std::map<std::string, Animation>> animation_group, bool static_view)
        : Entity(position, std::move(camera), viewSize, std::move(animation_group)), _static(static_view) {

}

bool UIWidget::is_static() const {
    return _static;
}
