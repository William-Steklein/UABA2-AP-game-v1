#ifndef GAMEENGINE_PHYSICSENTITY_H
#define GAMEENGINE_PHYSICSENTITY_H


#include "../Entity.h"

class PhysicsEntity : public Entity {
private:
    // physics

public:
    PhysicsEntity(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize,
                  std::shared_ptr<std::map<std::string, Animation>> animation_group);

    ~PhysicsEntity() = default;
};


#endif //GAMEENGINE_PHYSICSENTITY_H
