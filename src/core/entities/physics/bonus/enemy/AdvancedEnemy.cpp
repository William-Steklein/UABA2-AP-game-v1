#include "AdvancedEnemy.h"

AdvancedEnemy::AdvancedEnemy(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize,
                             AnimationPlayer animationPlayer, AudioPlayer audioPlayer, bool isStatic)
        : Enemy(position, std::move(camera), viewSize, std::move(animationPlayer), std::move(audioPlayer), isStatic) {
    // todo: constants
    _max_hit_points = 3;
    _current_hit_points = 3;
    _shoot_back = true;
}
