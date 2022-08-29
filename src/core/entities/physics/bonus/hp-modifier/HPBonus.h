#ifndef GAMEENGINE_HPBONUS_H
#define GAMEENGINE_HPBONUS_H


#include <utility>
#include "../Bonus.h"

class HPBonus : public Bonus {
private:
    unsigned int _hp_addition;

public:
    HPBonus(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize,
               AnimationPlayer animationPlayer = {}, AudioPlayer audioPlayer = {}, bool isStatic = false);

    void update(double t, float dt) override;

    void applyEffect() override;
};


#endif //GAMEENGINE_HPBONUS_H
