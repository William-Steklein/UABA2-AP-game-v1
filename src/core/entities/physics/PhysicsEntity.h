#ifndef GAMEENGINE_PHYSICSENTITY_H
#define GAMEENGINE_PHYSICSENTITY_H


#include "../Entity.h"
#include "../../physics/Ray.h"

class PhysicsEntity : public Entity {
protected:
    bool _is_static;

    // physics
    float _mass;
    Vector2f _force;
    Vector2f _velocity;
    Vector2f _acceleration;

    Vector2f _gravitational_acceleration;
    Vector2f _max_velocity;
    Vector2f _drag;
    Vector2f _friction;

    bool _passthrough;

public:
    PhysicsEntity(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize,
                  AnimationPlayer animation_player = {}, AudioPlayer audio_player = {},
                  bool is_static = false);

    ~PhysicsEntity() = default;

    void setupPlayerPhysics(float jump_dt, float jump_height);

    virtual void update(double t, float dt);

    bool isIsStatic() const;

    void setIsStatic(bool isStatic);

    float getMass() const;

    void setMass(float mass);

    const Vector2f &getForce() const;

    void setForce(const Vector2f &force);

    const Vector2f &getVelocity() const;

    void setVelocity(const Vector2f &velocity);

    const Vector2f &getAcceleration() const;

    void setAcceleration(const Vector2f &acceleration);

    void applyGravity();

    void applyFriction();

    void applyDrag();

    bool isPassthrough() const;

    void setPassthrough(bool passthrough);

    void applySideScrolling();

    virtual void resolveCollision(PhysicsEntity &other);
};


#endif //GAMEENGINE_PHYSICSENTITY_H
