#ifndef GAMEENGINE_HEART_H
#define GAMEENGINE_HEART_H


#include "../UIEntity.h"

class Heart : public UIEntity {
private:
    bool _full;

public:
    Heart(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize,
          AnimationPlayer animationPlayer = {}, AudioPlayer audioPlayer = {}, bool staticView = false);

    bool isFull() const;

    void setFull(bool full);
};


#endif //GAMEENGINE_HEART_H
