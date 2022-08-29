#ifndef GAMEENGINE_ENEMY_H
#define GAMEENGINE_ENEMY_H


#include <utility>
#include "../../PhysicsEntity.h"

class Enemy : public PhysicsEntity {
private:

public:
    Enemy(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize,
          AnimationPlayer animationPlayer = {}, AudioPlayer audioPlayer = {}, bool isStatic = false);

    void update(double t, float dt) override;
};


#endif //GAMEENGINE_ENEMY_H
