#ifndef GAMEENGINE_ENEMY_H
#define GAMEENGINE_ENEMY_H


#include <utility>
#include "../hp-modifier/SpikeBonus.h"

class Enemy : public SpikeBonus {
protected:
    bool _can_damage;
    float _damage_delay_time_passed;
    bool _shoot_back;

public:
    Enemy(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize,
          AnimationPlayer animationPlayer = {}, AudioPlayer audioPlayer = {}, bool isStatic = false);

    void update(double t, float dt) override;

    void applyEffect() override;

    bool isShootBack() const;
};


#endif //GAMEENGINE_ENEMY_H
