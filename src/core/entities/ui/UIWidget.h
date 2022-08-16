#ifndef GAMEENGINE_UIWIDGET_H
#define GAMEENGINE_UIWIDGET_H


#include "../Entity.h"
#include <memory>
#include <utility>

class UIWidget : public Entity {
private:
    bool _static;

public:
    UIWidget(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize,
             std::shared_ptr<std::map<std::string, AnimationPlayer>> animation_group,
             bool static_view = true);

    ~UIWidget() = default;

    bool is_static() const;
};


#endif //GAMEENGINE_UIWIDGET_H
