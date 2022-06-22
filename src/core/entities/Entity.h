#ifndef GAMEENGINE_ENTITY_H
#define GAMEENGINE_ENTITY_H


#include <memory>
#include <utility>
#include "../math/Vector2f.h"
#include "../Camera.h"
#include "../observer_pattern_interface/ISubject.h"

class Entity : public ISubject {
protected:
    // view
    std::shared_ptr<Camera> _camera;
    Vector2f _view_size;

    // transform
    Vector2f _position;
    Vector2f _scale;
    float _rotation;

public:
    Entity(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &view_size);

    virtual void update(double t, float dt);

    virtual Vector2f getViewSize() const;

    virtual Vector2f getGameViewSize() const;

    virtual void setViewSize(const Vector2f& view_size);

    virtual Vector2f getPosition() const;

    virtual Vector2f getGamePosition() const;

    virtual Vector2f getScale() const;

    virtual void setScale(const Vector2f& scale);

    virtual float getRotation() const;

    virtual void setRotation(float rotation);
};


#endif //GAMEENGINE_ENTITY_H
