#ifndef GAMEENGINE_VTELEPLATFORM_H
#define GAMEENGINE_VTELEPLATFORM_H


#include "Platform.h"
#include <utility>

class TelePlatform : public Platform {
private:
    bool _horizontal;
    bool _left;
    float _vertical_pivot;

public:
    TelePlatform(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize,
                 AnimationPlayer animationPlayer, AudioPlayer audioPlayer, bool isStatic);

    void update(double t, float dt) override;
};


#endif //GAMEENGINE_VTELEPLATFORM_H
