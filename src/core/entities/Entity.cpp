#include "Entity.h"

Entity::Entity(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &view_size)
    : _position(position), _scale({1, 1}), _camera(std::move(camera)), _view_size(view_size) {

}

void Entity::update(float t, float dt) {

    notifyObservers();
}

Vector2f Entity::getViewSize() const {
    return _view_size;
}

Vector2f Entity::getGameViewSize() const {
    return _camera->projectSize(_view_size);
}

void Entity::setViewSize(const Vector2f& view_size) {
    _view_size = view_size;
}

Vector2f Entity::getPosition() const {
    return _position;
}

Vector2f Entity::getGamePosition() const {
    return _camera->projectCoordinateCoreToGame(_position);
}

Vector2f Entity::getScale() const {
    return _scale;
}

void Entity::setScale(const Vector2f &scale) {
    _scale = scale;
}
