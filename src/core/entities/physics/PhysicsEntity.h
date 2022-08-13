#ifndef GAMEENGINE_PHYSICSENTITY_H
#define GAMEENGINE_PHYSICSENTITY_H


#include "../Entity.h"

class PhysicsEntity : public Entity {
protected:
    // physics
    float _mass;
    Vector2f _force;
    Vector2f _velocity;
    Vector2f _acceleration;

    bool _is_static;

public:
    PhysicsEntity(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize,
                  std::shared_ptr<std::map<std::string, Animation>> animation_group, float mass=1, bool is_static=false);

    ~PhysicsEntity() = default;

    virtual void update(double t, float dt);
};


#endif //GAMEENGINE_PHYSICSENTITY_H
