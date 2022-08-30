#ifndef GAMEENGINE_PLATFORM_H
#define GAMEENGINE_PLATFORM_H


#include "../PhysicsEntity.h"
#include "../bonus/Bonus.h"
#include "../../../Random.h"

class Platform : public PhysicsEntity {
protected:
    std::weak_ptr<Bonus> _bonus;
    Vector2f _bonus_offset;

public:
    Platform(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize,
             AnimationPlayer animationPlayer = {}, AudioPlayer audioPlayer = {}, bool isStatic = false);

    void addBonus(const std::weak_ptr<Bonus> &bonus);

    void setPosition(const Vector2f &position) override;
};


#endif //GAMEENGINE_PLATFORM_H
