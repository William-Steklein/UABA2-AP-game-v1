#ifndef GAMEENGINE_BONUS_H
#define GAMEENGINE_BONUS_H


#include <utility>
#include "../PhysicsEntity.h"

class Bonus : public PhysicsEntity {
private:

public:
    Bonus(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize,
          AnimationPlayer animationPlayer = {}, AudioPlayer audioPlayer = {}, bool isStatic = false);
};


#endif //GAMEENGINE_BONUS_H
