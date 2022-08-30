#ifndef GAMEENGINE_HPBAR_H
#define GAMEENGINE_HPBAR_H


#include "Heart.h"
#include "../../physics/PhysicsEntity.h"
#include <utility>

class HPBar : public UIEntity {
private:
    std::weak_ptr<PhysicsEntity> _affected_entity;
    std::vector<std::shared_ptr<Heart>> _hearts;
    unsigned int _nr_hp_max;
    unsigned int _nr_hp_current;

public:
    HPBar(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize,
          AnimationPlayer animationPlayer = {}, AudioPlayer audioPlayer = {}, bool staticView = false);

    void setHearts(std::weak_ptr<PhysicsEntity> entity, const std::weak_ptr<HPBar> &hp_bar_ptr, bool left_alligned,
                   const Vector2f &heart_size, const Vector2f &offset = {0, 0});

    std::vector<std::shared_ptr<Heart>> getHearts();

    void update(double t, float dt) override;

    void updateHearts(unsigned int current_hp);
};


#endif //GAMEENGINE_HPBAR_H
