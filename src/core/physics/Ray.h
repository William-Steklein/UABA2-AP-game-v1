#ifndef GAMEENGINE_RAY_H
#define GAMEENGINE_RAY_H


#include "../math/Vector2f.h"
#include "Hitbox.h"
#include "../math/math_funcs.h"

class Ray {
private:
    Vector2f _origin_point;
    Vector2f _end_point;

    bool _collided;
    Vector2f _collision_point;

public:
    Ray(const Vector2f &origin_point, const Vector2f &end_point);

    Ray(const Vector2f &origin_point, const Vector2f &direction, float length);

    const Vector2f &getOriginPoint() const;

    void setOriginPoint(const Vector2f &originPoint);

    const Vector2f &getEndPoint() const;

    void setEndPoint(const Vector2f &endPoint);

    void move(const Vector2f &vector);

    void scale(const Vector2f &scale, const Vector2f &origin={0, 0});

    bool isCollided() const;

    void setCollided(bool collided);

    const Vector2f &getCollisionPoint() const;

    void setCollisionPoint(const Vector2f &collisionPoint);

    void reset();

    bool collides(const Vector2f &other_origin_point, const Vector2f &other_end_point, bool set_collision_point = true);

    bool collides(const Ray &other, bool set_collision_point = true);

    bool collides(const Hitbox &other, bool set_collision_point = true);
};


#endif //GAMEENGINE_RAY_H
