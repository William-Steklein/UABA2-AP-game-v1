#include "UIWidget.h"

#include <utility>

UIWidget::UIWidget(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize, bool static_view)
        : Entity(position, std::move(camera), viewSize), _static_view(static_view) {

}

void UIWidget::update(double t, float dt) {
    if (!_static_view) {
        Entity::update(t, dt);
    }
}
