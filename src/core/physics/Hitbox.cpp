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
//    if (this->_position < other._position + other._size / 2) {
//        return (other._position - other._size / 2) - (this->_position + this->_size / 2);
//    } else {
//        return (other._position + other._size / 2) - (this->_position - this->_size / 2);
//    }

    Vector2f displacement;

//    if (this->_position.x < other._position.x + other._size.x / 2) {
//        displacement.x = (other._position.x - other._size.x / 2) - (this->_position.x + this->_size.x / 2);
//    } else {
//        displacement.x = (other._position.x + other._size.x / 2) - (this->_position.x - this->_size.x / 2);
//    }
//
//    if (this->_position.y < other._position.y + other._size.y / 2) {
//        displacement.y = (other._position.y - other._size.y / 2) - (this->_position.y + this->_size.y / 2);
//    } else {
//        displacement.y = (other._position.y + other._size.y / 2) - (this->_position.y - this->_size.y / 2);
//    }
//    
//    if (_position.x < other._position.x) {
//        displacement.x = other._position.x - (_position.x + _size.x);
//    } else {
//        displacement.x = _position.x - (other._position.x + other._size.x);
//    }
//
//    if (_position.y < other._position.y) {
//        displacement.y = other._position.y - (_position.y + _size.y);
//    } else {
//        displacement.y = _position.y - (other._position.y + other._size.y);
//    }

    Vector2f this_corner = _position - (_size / 2);
    Vector2f other_corner = other._position - (other._size / 2);

//    if (this_corner.x < other_corner.x) {
//        displacement.x = other_corner.x - (this_corner.x + _size.x);
//    } else {
//        displacement.x = this_corner.x - (other_corner.x + other._size.x);
//    }
//
//    if (this_corner.y < other_corner.y) {
//        displacement.y = other_corner.y - (this_corner.y + _size.y);
//    } else {
//        displacement.y = this_corner.y - (other_corner.y + other._size.y);
//    }

    if (_position.x - (_size.x / 2) < other._position.x - (other._size.x / 2)) {
        displacement.x = other._position.x - (other._size.x / 2) - (_position.x - (_size.x / 2) + _size.x);
    } else {
        displacement.x = _position.x - (_size.x / 2) - (other._position.x - (other._size.x / 2) + other._size.x);
    }

    if (_position.y - (_size.y / 2) < other._position.y - (other._size.y / 2)) {
        displacement.y = other._position.y - (other._size.y / 2) - (_position.y - (_size.y / 2) + _size.y);
    } else {
        displacement.y = _position.y - (_size.y / 2) - (other._position.y - (other._size.y / 2) + other._size.y);
    }


    return displacement;
}
