#include "Ray.h"

Ray::Ray(const Vector2f &origin_point, const Vector2f &end_point) : _origin_point(origin_point), _end_point(end_point) {

}

Ray::Ray(const Vector2f &origin_point, const Vector2f &direction, float length) : _origin_point(origin_point) {
    _end_point = _origin_point + direction * length;
}

const Vector2f &Ray::getOriginPoint() const {
    return _origin_point;
}

void Ray::setOriginPoint(const Vector2f &originPoint) {
    _origin_point = originPoint;
}

const Vector2f &Ray::getEndPoint() const {
    return _end_point;
}

void Ray::setEndPoint(const Vector2f &endPoint) {
    _end_point = endPoint;
}

bool Ray::isActivated() const {
    return _activated;
}

void Ray::setActivated(bool activated) {
    _activated = activated;
}

const Vector2f &Ray::getCollisionPoint() const {
    return _collision_point;
}

void Ray::setCollisionPoint(const Vector2f &collisionPoint) {
    _collision_point = collisionPoint;
}

bool Ray::collides(const Vector2f &other_origin_point, const Vector2f &other_end_point) const {
    // todo: implement line segment collision detection
    return false;
}

bool Ray::collides(const Ray &other) {
    // todo: implement line segment collision detection
    return false;
}

bool Ray::collides(const Hitbox &other) {
    // todo: implement line segment collision detection
    return false;
}
