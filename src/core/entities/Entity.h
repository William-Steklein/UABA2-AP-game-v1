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
#include "../animation/AnimationPlayer.h"
#include "../physics/Hitbox.h"
#include "../physics/Ray.h"
#include "../audio/AudioPlayer.h"

class Entity : public ISubject {
protected:
    // transform
    Vector2f _position;
    Vector2f _scale;
    float _rotation;

    // view
    std::shared_ptr<Camera> _camera;
    Vector2f _view_size;

    // physics
    std::shared_ptr<Hitbox> _hitbox;
    std::vector<std::shared_ptr<Ray>> _rays;

    // resource players
    AnimationPlayer _animation_player;
    AudioPlayer _audio_player;

public:
    Entity(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &view_size,
           AnimationPlayer animation_player = {}, AudioPlayer audio_player = {});

    virtual void update(double t, float dt);

    virtual void updateView();

    virtual Vector2f getPosition() const;

    virtual Vector2f getScreenPosition() const;

    virtual void setPosition(const Vector2f &position);

    void move(const Vector2f &vector);

    virtual Vector2f getScale() const;

    virtual void setScale(const Vector2f &scale);

    virtual void scale(const Vector2f &scale);

    virtual float getRotation() const;

    virtual void setRotation(float rotation);

    virtual void rotate(float rotation);

    virtual Vector2f getViewSize() const;

    virtual Vector2f getScreenViewSize() const;

    virtual void setViewSize(const Vector2f &view_size);

    const std::shared_ptr<Hitbox> &getHitbox();

    std::shared_ptr<Hitbox> getScreenHitbox();

    void setHitbox(const Vector2f &position, const Vector2f &size);

    void setHitbox(const Hitbox &hitbox);

    void setHitbox(const std::shared_ptr<Hitbox> &hitbox);

    const std::vector<std::shared_ptr<Ray>> &getRays() const;

    std::vector<std::shared_ptr<Ray>> getScreenRays() const;

    void setRays(const std::vector<std::shared_ptr<Ray>> &rays);

    std::string getTextureGroupName() const;

    bool isHorizontalMirror() const;

    unsigned int getCurrentTextureIndex() const;

    void updateAnimationFrame();

    void playAnimation(const std::string &animation_name);

    void playSound(const std::string &sound_name);

    void playMusic(const std::string &music_name);

    bool isAudioLoop() const;

    bool isAudioFinish() const;

    float getSpatialAudioLevel() const;
};


#endif //GAMEENGINE_ENTITY_H
