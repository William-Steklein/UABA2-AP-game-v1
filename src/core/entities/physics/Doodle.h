#ifndef GAMEENGINE_DOODLE_H
#define GAMEENGINE_DOODLE_H


#include "PhysicsEntity.h"
#include <map>
#include "../../animation/AnimationData.h"

class Doodle : public PhysicsEntity {
private:
    std::map<std::string, AnimationData> _animations;
    std::string _current_animation_name;
    unsigned int _current_animation_frame;
    float _current_animation_time;

    double _prev_t;
    bool _facing_left;

public:
    Doodle(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize);

    void update(double t, float dt) override;

    void startAnimation(const std::string &animation_name);

    void advanceAnimation();
};


#endif //GAMEENGINE_DOODLE_H
