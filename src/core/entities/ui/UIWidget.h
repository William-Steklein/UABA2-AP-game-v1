#ifndef GAMEENGINE_UIWIDGET_H
#define GAMEENGINE_UIWIDGET_H


#include "../Entity.h"
#include <memory>
#include <utility>

class UIWidget : public Entity {
private:
    bool _static_view;

public:
    UIWidget(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &view_size,
             AnimationPlayer animation_player = {}, AudioPlayer audio_player = {}, bool static_view = true);

    ~UIWidget() = default;

    bool is_static_view() const;
};


#endif //GAMEENGINE_UIWIDGET_H
