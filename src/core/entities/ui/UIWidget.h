#ifndef GAMEENGINE_UIWIDGET_H
#define GAMEENGINE_UIWIDGET_H


#include "../Entity.h"

class UIWidget : public Entity {
private:
    bool _static_view;

public:
    UIWidget(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize,
             bool static_view=true);

    ~UIWidget() = default;

    void update(double t, float dt) override;
};


#endif //GAMEENGINE_UIWIDGET_H
