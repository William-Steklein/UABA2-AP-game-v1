#ifndef GAMEENGINE_TEMPPLATFORM_H
#define GAMEENGINE_TEMPPLATFORM_H


#include "Platform.h"

class TempPlatform : public Platform {
private:

public:
    TempPlatform(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize,
                 AnimationPlayer animationPlayer = {}, AudioPlayer audioPlayer = {}, bool isStatic = false);

    void update(double t, float dt) override;
};


#endif //GAMEENGINE_TEMPPLATFORM_H
