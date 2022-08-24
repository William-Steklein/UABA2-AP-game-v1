#ifndef GAMEENGINE_PLATFORM_H
#define GAMEENGINE_PLATFORM_H


#include "../PhysicsEntity.h"

class Platform : public PhysicsEntity {

public:
    Platform(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize,
             AnimationPlayer animationPlayer, AudioPlayer audioPlayer, bool isStatic);
};


#endif //GAMEENGINE_PLATFORM_H
