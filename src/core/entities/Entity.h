#ifndef GAMEENGINE_ENTITY_H
#define GAMEENGINE_ENTITY_H


#include <memory>
#include <utility>
#include <vector>
#include <map>
#include "../math/Vector2f.h"
#include "../Camera.h"
#include "../observer-pattern-interface/ISubject.h"
#include "../animation/Animation.h"

class Entity : public ISubject {
protected:
    // view
    std::shared_ptr<Camera> _camera;
    Vector2f _view_size;

    std::shared_ptr<std::map<std::string, Animation>> _animation_group;
    std::string _current_animation_name;
    bool _h_mirror;
    unsigned int _current_animation_frame;
    float _current_animation_time;

    // transform
    Vector2f _position;
    Vector2f _scale;
    float _rotation;

public:
    Entity(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &view_size,
           std::shared_ptr<std::map<std::string, Animation>> animation_group);

    virtual void update(double t, float dt);

    virtual Vector2f getViewSize() const;

    virtual Vector2f getGameViewSize() const;

    virtual void setViewSize(const Vector2f &view_size);

    virtual Vector2f getPosition() const;

    virtual Vector2f getGamePosition() const;

    virtual Vector2f getScale() const;

    virtual void setScale(const Vector2f &scale);

    virtual float getRotation() const;

    virtual void setRotation(float rotation);

    unsigned int getCurrentTextureIndex() const;

    bool isMirrored() const;

    void updateAnimationFrame();

    void startAnimation(const std::string &animation_name, bool mirrored=false);

    void advanceAnimation();
};


#endif //GAMEENGINE_ENTITY_H
