#ifndef GAMEENGINE_BULLET_H
#define GAMEENGINE_BULLET_H


#include "PhysicsEntity.h"
#include <utility>

class Bullet : public PhysicsEntity {
private:
    bool _up;

public:
    Bullet(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize, bool up = true,
           AnimationPlayer animationPlayer = {}, AudioPlayer audioPlayer = {}, bool isStatic = false);

    void update(double t, float dt) override;
};


#endif //GAMEENGINE_BULLET_H
