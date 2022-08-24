#ifndef GAMEENGINE_VTELEPLATFORM_H
#define GAMEENGINE_VTELEPLATFORM_H


#include <utility>
#include "Platform.h"
#include "../../../Random.h"

class TelePlatform : public Platform {
private:
    bool _horizontal;
    Vector2f _bounderies;

public:
    TelePlatform(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize, bool horizontal,
                 AnimationPlayer animationPlayer = {}, AudioPlayer audioPlayer = {}, bool isStatic = false);

    void update(double t, float dt) override;
};


#endif //GAMEENGINE_VTELEPLATFORM_H
