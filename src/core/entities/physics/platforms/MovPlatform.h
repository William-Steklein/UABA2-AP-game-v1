#ifndef GAMEENGINE_VMOVPLATFORM_H
#define GAMEENGINE_VMOVPLATFORM_H


#include <utility>
#include "Platform.h"
#include "../../../Random.h"
#include "../../../constants/constants.h"

class MovPlatform : public Platform {
private:
    bool _horizontal;
    bool _going_left;

    Vector2f _bounderies;

public:
    MovPlatform(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize, bool horizontal,
                AnimationPlayer animationPlayer = {}, AudioPlayer audioPlayer = {}, bool isStatic = false);

    void update(double t, float dt) override;
};


#endif //GAMEENGINE_VMOVPLATFORM_H
