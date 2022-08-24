#ifndef GAMEENGINE_VMOVPLATFORM_H
#define GAMEENGINE_VMOVPLATFORM_H


#include "Platform.h"
#include <utility>
#include "../../../constants/constants.h"

class MovPlatform : public Platform {
private:
    bool _horizontal;
    bool _going_left;
    float _vertical_pivot;

public:
    MovPlatform(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize,
                AnimationPlayer animationPlayer, AudioPlayer audioPlayer, bool isStatic);

    void update(double t, float dt) override;
};


#endif //GAMEENGINE_VMOVPLATFORM_H
