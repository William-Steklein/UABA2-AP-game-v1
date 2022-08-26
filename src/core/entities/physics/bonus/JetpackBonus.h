#ifndef GAMEENGINE_JETPACKBONUS_H
#define GAMEENGINE_JETPACKBONUS_H


#include <utility>
#include "Bonus.h"

class JetpackBonus : public Bonus {
private:
    float _time_passed;

public:
    JetpackBonus(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize,
                 AnimationPlayer animationPlayer = {}, AudioPlayer audioPlayer = {}, bool isStatic = false);

    void update(double t, float dt) override;

    void applyEffect() override;
};


#endif //GAMEENGINE_JETPACKBONUS_H
