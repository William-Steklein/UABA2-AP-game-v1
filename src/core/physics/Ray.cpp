#include "Ray.h"

Ray::Ray(const Vector2f &origin_point, const Vector2f &end_point) : _origin_point(origin_point), _end_point(end_point),
                                                                    _collided(false) {

}

Ray::Ray(const Vector2f &origin_point, const Vector2f &direction, float length) : Ray(origin_point, origin_point +
                                                                                                    direction *
                                                                                                    length) {

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

void Ray::move(const Vector2f &vector) {
    _origin_point += vector;
    _end_point += vector;
    _collision_point += vector;
}

void Ray::scale(const Vector2f &scale, const Vector2f &origin) {
    _origin_point = {(_origin_point.x + origin.x * scale.x) - origin.x,
                     (_origin_point.y + origin.y * scale.y) - origin.y};
    _end_point = {(_end_point.x + origin.x * scale.x) - origin.x, (_end_point.y + origin.y * scale.y) - origin.y};
    _collision_point = {(_collision_point.x + origin.x * scale.x) - origin.x,
                        (_collision_point.y + origin.y * scale.y) - origin.y};
}

bool Ray::isCollided() const {
    return _collided;
}

void Ray::setCollided(bool collided) {
    _collided = collided;
}

const Vector2f &Ray::getCollisionPoint() const {
    return _collision_point;
}

void Ray::setCollisionPoint(const Vector2f &collisionPoint) {
    _collision_point = collisionPoint;
}

void Ray::reset() {
    _collided = false;
    _collision_point.clear();
}

bool Ray::collides(const Vector2f &other_origin_point, const Vector2f &other_end_point, bool set_collision_point) {
    Vector2f intersection1;
    Vector2f intersection2;
    bool is_collinear = false;

    bool collision = linesegmentIntersection(_origin_point, _end_point, other_origin_point, other_end_point,
                                             intersection1, intersection2, is_collinear);

    if (collision && set_collision_point) {
        Vector2f closest_intersection;
        if (is_collinear) {
            // check the closest intersection of 1 & 2
            if ((intersection1 - _origin_point).length() < (intersection2 - _origin_point).length()) {
                closest_intersection = intersection1;
            } else {
                closest_intersection = intersection2;
            }
        } else {
            closest_intersection = intersection1;
        }

        // check the closest point of closest intersection and previous intersection;
        if (_collided) {
            if ((closest_intersection - _origin_point).length() < (_collision_point - _origin_point).length()) {
                _collision_point = closest_intersection;
            }
            _collided = true;
        } else {
            _collision_point = closest_intersection;
            _collided = true;
        }
    }

    return collision;
}

bool Ray::collides(const Ray &other, bool set_collision_point) {
    return collides(other._origin_point, other._end_point, set_collision_point);
}

bool Ray::collides(const Hitbox &other, bool set_collision_point) {
    Vector2f h0 = other.getPosition() - other.getSize() / 2;
    Vector2f h1 = {h0.x + other.getSize().x, h0.y};
    Vector2f h2 = {h0.x + other.getSize().x, h0.y + other.getSize().y};
    Vector2f h3 = {h0.x, h0.y + other.getSize().y};

    return collides(h0, h1, set_collision_point) || collides(h1, h2, set_collision_point) ||
           collides(h2, h3, set_collision_point) || collides(h3, h0, set_collision_point);
}
