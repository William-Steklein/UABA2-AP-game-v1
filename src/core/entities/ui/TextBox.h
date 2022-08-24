#ifndef GAMEENGINE_TEXTBOX_H
#define GAMEENGINE_TEXTBOX_H


#include "UIWidget.h"
#include <utility>
#include <string>

class TextBox : public UIWidget {
private:
    std::shared_ptr<std::string> _text;

public:
    TextBox(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize,
            std::shared_ptr<std::string> text, AnimationPlayer animationPlayer = {}, AudioPlayer audioPlayer = {},
            bool staticView = false);

    std::shared_ptr<std::string> getText();
};


#endif //GAMEENGINE_TEXTBOX_H