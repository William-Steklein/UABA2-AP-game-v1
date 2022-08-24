#ifndef GAMEENGINE_DISAPPEARINGPLATFORM_H
#define GAMEENGINE_DISAPPEARINGPLATFORM_H


#include "Platform.h"

class DisappearingPlatform : public Platform {
private:

public:
    DisappearingPlatform(const Vector2f &position, std::shared_ptr<Camera> camera,
                         const Vector2f &viewSize, AnimationPlayer animationPlayer,
                         AudioPlayer audioPlayer, bool isStatic);

    void update(double t, float dt) override;
};


#endif //GAMEENGINE_DISAPPEARINGPLATFORM_H
