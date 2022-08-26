#ifndef GAMEENGINE_UIENTITY_H
#define GAMEENGINE_UIENTITY_H


#include "../Entity.h"
#include <memory>
#include <utility>

class UIEntity : public Entity {
private:
    bool _static_view;

public:
    UIEntity(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &view_size,
             AnimationPlayer animation_player = {}, AudioPlayer audio_player = {}, bool static_view = true);

    ~UIEntity() = default;

    bool is_static_view() const;
};


#endif //GAMEENGINE_UIENTITY_H
