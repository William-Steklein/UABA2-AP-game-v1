#ifndef GAMEENGINE_SPIKEBONUS_H
#define GAMEENGINE_SPIKEBONUS_H


#include <utility>
#include "../Bonus.h"

class SpikeBonus : public Bonus {
private:
    unsigned int _damage;

public:
    SpikeBonus(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize,
               AnimationPlayer animationPlayer = {}, AudioPlayer audioPlayer = {}, bool isStatic = false);

    void update(double t, float dt) override;

    void applyEffect() override;
};


#endif //GAMEENGINE_SPIKEBONUS_H
