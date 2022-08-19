#ifndef GAMEENGINE_PORTALRADIO_H
#define GAMEENGINE_PORTALRADIO_H


#include "PhysicsEntity.h"
#include <utility>

class PortalRadio : public PhysicsEntity {
private:
    bool start = false;
public:
    PortalRadio(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize,
                AnimationPlayer animation_player = {}, AudioPlayer audio_player = {}, bool is_static = false);

    void update(double t, float dt) override;
};


#endif //GAMEENGINE_PORTALRADIO_H
