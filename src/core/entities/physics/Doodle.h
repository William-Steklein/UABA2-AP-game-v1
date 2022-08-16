#ifndef GAMEENGINE_DOODLE_H
#define GAMEENGINE_DOODLE_H


#include "PhysicsEntity.h"
#include "../../InputMap.h"
#include <utility>

class Doodle : public PhysicsEntity {
private:
    bool _standing{false};
    bool _hit_platform{false};

    float _initial_jump_velocity;
    float _horizontal_movement_force;

    float _drag;
    float _friction;
    Vector2f _max_velocity;

    std::shared_ptr<InputMap> _input_map;

public:
    Doodle(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize,
           std::shared_ptr<std::map<std::string, AnimationPlayer>> animation_group, std::shared_ptr<InputMap> input_map,
           float mass = 1, bool is_static = false);

    void update(double t, float dt) override;

    void testController();

    void testController2();

    void adventurerController();
};


#endif //GAMEENGINE_DOODLE_H
