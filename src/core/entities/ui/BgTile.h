#ifndef GAMEENGINE_BGTILE_H
#define GAMEENGINE_BGTILE_H


#include <utility>
#include "UIEntity.h"

class BgTile : public UIEntity {
private:

public:
    BgTile(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize,
           AnimationPlayer animationPlayer = {}, AudioPlayer audioPlayer = {}, bool staticView = false);
};


#endif //GAMEENGINE_BGTILE_H
