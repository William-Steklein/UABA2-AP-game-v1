#ifndef GAMEENGINE_BUTTON_H
#define GAMEENGINE_BUTTON_H


#include "UIWidget.h"

class Button : public UIWidget {
private:
    bool _pressed;

public:
    Button(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize,
           AnimationPlayer animationPlayer = {}, AudioPlayer audioPlayer = {}, bool staticView=false);

    virtual void update(double t, float dt) override;

    bool isPressed() const;

    void setPressed(bool pressed);
};


#endif //GAMEENGINE_BUTTON_H
