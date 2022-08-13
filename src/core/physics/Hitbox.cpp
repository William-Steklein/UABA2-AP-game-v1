#include "Hitbox.h"

Hitbox::Hitbox(const Vector2f &position, const Vector2f &size) : _position(position), _size(size) {

}

const Vector2f &Hitbox::getPosition() const {
    return _position;
}

void Hitbox::setPosition(const Vector2f &position) {
    _position = position;
}

const Vector2f &Hitbox::getSize() const {
    return _size;
}

void Hitbox::setSize(const Vector2f &size) {
    _size = size;
}

bool Hitbox::collides(const Hitbox &other) const {
    // todo: AABB collision detection

    return false;
}
