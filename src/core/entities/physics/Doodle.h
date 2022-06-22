#ifndef GAMEENGINE_DOODLE_H
#define GAMEENGINE_DOODLE_H


#include "../Entity.h"

class Doodle : public Entity {

public:
    Doodle(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize);

    void update(double t, float dt) override;

    void jump();
};


#endif //GAMEENGINE_DOODLE_H
