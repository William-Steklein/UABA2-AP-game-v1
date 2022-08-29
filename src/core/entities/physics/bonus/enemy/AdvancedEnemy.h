#ifndef GAMEENGINE_ADVANCEDENEMY_H
#define GAMEENGINE_ADVANCEDENEMY_H


#include "Enemy.h"
#include <utility>

class AdvancedEnemy : public Enemy {
public:
    AdvancedEnemy(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize,
                  AnimationPlayer animationPlayer = {}, AudioPlayer audioPlayer = {}, bool isStatic = false);
};


#endif //GAMEENGINE_ADVANCEDENEMY_H
