#ifndef GAMEENGINE_DOODLE_H
#define GAMEENGINE_DOODLE_H


#include <utility>
#include "PhysicsEntity.h"
#include "../../InputMap.h"
#include "../../constants/constants.h"

class Doodle : public PhysicsEntity {
private:
    bool _standing;
    bool _jumped;

    float _initial_jump_velocity;
    float _horizontal_movement_force;

    std::shared_ptr<InputMap> _input_map;

public:
    Doodle(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize,
           std::shared_ptr<InputMap> input_map, AnimationPlayer animation_player = {}, AudioPlayer audio_player = {},
           bool is_static = false);

    void update(double t, float dt) override;

    void reset();

    void playerController();

    float getInitialJumpVelocity() const;

    float getHorizontalMovementForce() const;
};


#endif //GAMEENGINE_DOODLE_H
