#ifndef GAMEENGINE_DOODLE_H
#define GAMEENGINE_DOODLE_H


#include "PhysicsEntity.h"
#include <map>
#include "../../animation/Animation.h"

class Doodle : public PhysicsEntity {
private:
    bool _standing{false};
    bool _hit_platform{false};

    float _gravitational_acceleration;
    float _initial_jump_velocity;
    float _horizontal_movement_force;

    float _drag;
    float _friction;
    Vector2f _max_velocity;

    double _prev_t;
    unsigned int _current_animation;
    bool _facing_left;

public:
    Doodle(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize,
           std::shared_ptr<std::map<std::string, Animation>> animation_group, float mass=1, bool is_static=false);

    void update(double t, float dt) override;
};


#endif //GAMEENGINE_DOODLE_H
