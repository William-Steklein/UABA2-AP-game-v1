#ifndef GAMEENGINE_PORTALRADIO_H
#define GAMEENGINE_PORTALRADIO_H


#include "PhysicsEntity.h"

class PortalRadio : public PhysicsEntity {
private:

public:
    PortalRadio(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize,
                std::shared_ptr<std::map<std::string, AnimationPlayer>> animationGroup, float mass = 1,
                bool isStatic = false);

    void update(double t, float dt) override;
};


#endif //GAMEENGINE_PORTALRADIO_H
