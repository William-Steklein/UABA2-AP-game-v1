#ifndef GAMEENGINE_WALL_H
#define GAMEENGINE_WALL_H


#include "PhysicsEntity.h"
#include <utility>

class Wall : public PhysicsEntity {
public:
    Wall(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize,
         std::shared_ptr<std::map<std::string, Animation>> animation_group, float mass=1, bool is_static=true);
};


#endif //GAMEENGINE_WALL_H
