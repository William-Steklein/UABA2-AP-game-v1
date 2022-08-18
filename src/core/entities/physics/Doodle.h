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

    std::shared_ptr<InputMap> _input_map;

public:
    Doodle(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize,
           std::shared_ptr<InputMap> input_map, AnimationPlayer animation_player = {}, AudioPlayer audio_player = {},
           bool is_static = false);

    void update(double t, float dt) override;

    void reset();

    void playerController(float dt);

    void testController();
};


#endif //GAMEENGINE_DOODLE_H
