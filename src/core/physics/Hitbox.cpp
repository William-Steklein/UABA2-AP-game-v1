#include "Hitbox.h"

Hitbox::Hitbox(const Vector2f &position, const Vector2f &size, const Vector2f &offset) : _position(position),
                                                                                         _original_position(position),
                                                                                         _size(size),
                                                                                         _offset(offset) {

}

const Vector2f &Hitbox::getPosition() const {
    return _position;
}

void Hitbox::setPosition(const Vector2f &position) {
    _original_position = position;
    _position = _original_position + _offset;
}

const Vector2f &Hitbox::getSize() const {
    return _size;
}

void Hitbox::setSize(const Vector2f &size) {
    _size = size;
}

const Vector2f &Hitbox::getOffset() const {
    return _offset;
}

void Hitbox::setOffset(const Vector2f &offset) {
    _offset = offset;
}

void Hitbox::scale(const Vector2f &scale) {
    _offset = {_offset.x * scale.x, _offset.y * scale.y};
    _size = {_size.x * scale.x, _size.y * scale.y};

    setPosition(_original_position);
}

bool Hitbox::empty() const {
    return _size.empty();
}

bool Hitbox::collides(const Hitbox &other) const {
    return this->_position.x - this->_size.x / 2 < other._position.x + other._size.x / 2 &&
           this->_position.x + this->_size.x / 2 > other._position.x - other._size.x / 2 &&
           this->_position.y - this->_size.y / 2 < other._position.y + other._size.y / 2 &&
           this->_position.y + this->_size.y / 2 > other._position.y - other._size.y / 2;
}

Vector2f Hitbox::getDisplacementToCollision(const Hitbox &other) const {
    Vector2f displacement;

    if (_position.x < other._position.x) {
        displacement.x = other._position.x - (other._size.x / 2) - (_position.x + (_size.x / 2));
    } else {
        displacement.x = other._position.x + (other._size.x / 2) - (_position.x - (_size.x / 2));
    }

    if (_position.y < other._position.y) {
        displacement.y = other._position.y - (other._size.y / 2) - (_position.y + (_size.y / 2));
    } else {
        displacement.y = other._position.y + (other._size.y / 2) - (_position.y - (_size.y / 2));
    }

    return displacement;
}
