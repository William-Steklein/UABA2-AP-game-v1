#include "UIWidget.h"

#include <utility>

UIWidget::UIWidget(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize, bool static_view)
        : Entity(position, std::move(camera), viewSize), _static(static_view) {

}

bool UIWidget::is_static() const {
    return _static;
}
