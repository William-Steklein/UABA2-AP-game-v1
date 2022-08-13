#ifndef GAMEENGINE_RAY_H
#define GAMEENGINE_RAY_H


#include "../math/Vector2f.h"
#include "Hitbox.h"

class Ray {
private:
    Vector2f _origin_point;
    Vector2f _end_point;

    bool _activated;
    Vector2f _collision_point;

public:
    Ray(const Vector2f &origin_point, const Vector2f &end_point);

    Ray(const Vector2f &origin_point, const Vector2f &direction, float length);

    const Vector2f &getOriginPoint() const;

    void setOriginPoint(const Vector2f &originPoint);

    const Vector2f &getEndPoint() const;

    void setEndPoint(const Vector2f &endPoint);

    bool isActivated() const;

    void setActivated(bool activated);

    const Vector2f &getCollisionPoint() const;

    void setCollisionPoint(const Vector2f &collisionPoint);

    bool collides(const Vector2f &other_origin_point, const Vector2f &other_end_point) const;

    bool collides(const Ray &other);

    bool collides(const Hitbox &other);
};


#endif //GAMEENGINE_RAY_H
