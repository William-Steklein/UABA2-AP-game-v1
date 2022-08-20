#ifndef GAMEENGINE_TEXT_H
#define GAMEENGINE_TEXT_H


#include "UIWidget.h"
#include <utility>

class Text : public UIWidget {
private:


public:
    Text(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize,
         AnimationPlayer animationPlayer = {}, AudioPlayer audioPlayer = {}, bool staticView=false);
};


#endif //GAMEENGINE_TEXT_H
