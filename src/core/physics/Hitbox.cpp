#include "Hitbox.h"

Hitbox::Hitbox(const Vector2f &position, const Vector2f &size, const Vector2f &offset) : _position(position),
                                                                                         _original_position(position),
                                                                                         _scale({1.f, 1.f}),
                                                                                         _size(size),
                                                                                         _original_size(size),
                                                                                         _offset(offset),
                                                                                         _original_offset(offset) {

}

const Vector2f &Hitbox::getPosition() const {
    return _position;
}

void Hitbox::setPosition(const Vector2f &position) {
    _original_position = position;
    _position = _original_position + _offset;
}

const Vector2f &Hitbox::getScale() const {
    return _scale;
}

void Hitbox::setScale(const Vector2f &scale) {
    _scale = scale;

    setSize(_original_size);

    setOffset(_original_offset);
    setPosition(_original_position);
}

const Vector2f &Hitbox::getSize() const {
    return _size;
}

void Hitbox::setSize(const Vector2f &size) {
    _original_size = size;
    _size = {_original_size.x * _scale.x, _original_size.y * _scale.y};
}

const Vector2f &Hitbox::getOffset() const {
    return _offset;
}

void Hitbox::setOffset(const Vector2f &offset) {
    _original_offset = offset;
    _offset = {_original_offset.x * _scale.x, _original_offset.y * _scale.y};
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
    if (_position < other._position) {
        return other._position - (other._size / 2) - (_position + (_size / 2));
    } else {
        return other._position + (other._size / 2) - (_position - (_size / 2));
    }
}
