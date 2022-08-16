#ifndef GAMEENGINE_ENTITY_H
#define GAMEENGINE_ENTITY_H


#include <memory>
#include <utility>
#include <vector>
#include <map>
#include "../math/Vector2f.h"
#include "../Camera.h"
#include "../observer-pattern-interface/ISubject.h"
#include "../animation/AnimationPlayer.h"
#include "../physics/Hitbox.h"

class Entity : public ISubject {
protected:
    // transform
    Vector2f _position;
    Vector2f _scale;
    float _rotation;

    // view
    std::shared_ptr<Camera> _camera;
    Vector2f _view_size;

    // animation player
    std::shared_ptr<std::map<std::string, AnimationPlayer>> _animation_group;
    std::string _current_animation_name;
    bool _h_mirror;
    unsigned int _current_animation_frame;
    float _current_animation_time;

    // audio player

    // physics hitbox
    std::shared_ptr<Hitbox> _hitbox;
    Vector2f _hitbox_offset;

public:
    Entity(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &view_size,
           std::shared_ptr<std::map<std::string, AnimationPlayer>> animation_group);

    virtual void update(double t, float dt);

    virtual void updateView();

    virtual Vector2f getPosition() const;

    virtual Vector2f getScreenPosition() const;

    virtual void setPosition(const Vector2f &position);

    void move(const Vector2f& vector);

    virtual Vector2f getScale() const;

    virtual void setScale(const Vector2f &scale);

    virtual float getRotation() const;

    virtual void setRotation(float rotation);

    virtual Vector2f getViewSize() const;

    virtual Vector2f getScreenViewSize() const;

    virtual void setViewSize(const Vector2f &view_size);

    unsigned int getCurrentTextureIndex() const;

    bool isMirrored() const;

    void updateAnimationFrame();

    void startAnimation(const std::string &animation_name, bool mirrored=false);

    void advanceAnimation();

    std::shared_ptr<Hitbox> getHitbox();

    Hitbox getScreenHitbox();

    void setHitbox(const Vector2f &position, const Vector2f &size);

    void setHitbox(const Hitbox &hitbox);

    void setHitbox(const std::shared_ptr<Hitbox> &hitbox);

    void setHitboxOffset(const Vector2f &hitbox_offset);
};


#endif //GAMEENGINE_ENTITY_H
