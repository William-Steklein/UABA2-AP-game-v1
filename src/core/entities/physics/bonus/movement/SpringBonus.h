#ifndef GAMEENGINE_SPRINGBONUS_H
#define GAMEENGINE_SPRINGBONUS_H


#include "../Bonus.h"
#include "../../../../constants/constants.h"
#include <utility>

class SpringBonus : public Bonus {
public:
    SpringBonus(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize,
                AnimationPlayer animationPlayer = {}, AudioPlayer audioPlayer = {}, bool isStatic = false);

private:
    void applyEffect() override;
};


#endif //GAMEENGINE_SPRINGBONUS_H
