#include "Heart.h"

#include <utility>

Heart::Heart(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize,
             AnimationPlayer animationPlayer, AudioPlayer audioPlayer, bool staticView)
        : UIEntity(position, std::move(camera), viewSize, std::move(animationPlayer), std::move(audioPlayer),
                   staticView), _full(true) {
    playAnimation("red");
}

bool Heart::isFull() const {
    return _full;
}

void Heart::setFull(bool full) {
    _full = full;
    if (_full) {
        playAnimation("red");
    } else {
        playAnimation("black");
    }
}
