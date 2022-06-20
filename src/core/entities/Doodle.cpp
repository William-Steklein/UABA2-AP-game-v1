#include "Doodle.h"

Doodle::Doodle(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize)
        : Entity(position, camera, viewSize) {

}
