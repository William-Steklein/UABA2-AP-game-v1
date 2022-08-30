#ifndef GAMEENGINE_BONUS_H
#define GAMEENGINE_BONUS_H


#include <utility>
#include "../PhysicsEntity.h"

class Bonus : public PhysicsEntity {
protected:
    std::weak_ptr<PhysicsEntity> _affected_entity;
    bool _active;

public:
    Bonus(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize,
          AnimationPlayer animationPlayer = {}, AudioPlayer audioPlayer = {}, bool isStatic = false);

    void update(double t, float dt) override;

    virtual void applyEntity(const std::weak_ptr<PhysicsEntity> &other);

    bool isActive() const;

private:
    virtual void applyEffect() = 0;
};


#endif //GAMEENGINE_BONUS_H
