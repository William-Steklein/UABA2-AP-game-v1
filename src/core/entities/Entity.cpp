#include "Entity.h"

Entity::Entity(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &view_size,
               std::shared_ptr<std::map<std::string, AnimationPlayer>> animation_group)
        : _position(position), _scale({1, 1}), _rotation(0), _camera(std::move(camera)), _view_size(view_size),
          _animation_group(std::move(animation_group)), _current_animation_name(""), _h_mirror(false),
          _current_animation_frame(0), _current_animation_time(0), _hitbox(std::make_shared<Hitbox>()) {

}

void Entity::update(double t, float dt) {
    advanceAnimation();
    updateView();
}

void Entity::updateView() {
    notifyObservers();
}

Vector2f Entity::getPosition() const {
    return _position;
}

Vector2f Entity::getScreenPosition() const {
    return _camera->projectCoordCoreToGame(_position);
}

void Entity::setPosition(const Vector2f &position) {
    _position = position;
    _hitbox->setPosition(_position + _hitbox_offset);
}

void Entity::move(const Vector2f &vector) {
    setPosition(_position + vector);
}

Vector2f Entity::getScale() const {
    return _scale;
}

void Entity::setScale(const Vector2f &scale) {
    _scale = scale;
}

float Entity::getRotation() const {
    return _rotation;
}

void Entity::setRotation(float rotation) {
    _rotation = rotation;
}

Vector2f Entity::getViewSize() const {
    return _view_size;
}

Vector2f Entity::getScreenViewSize() const {
    return _camera->projectSizeCoreToGame(_view_size);
}

void Entity::setViewSize(const Vector2f &view_size) {
    _view_size = view_size;
}

unsigned int Entity::getCurrentTextureIndex() const {
    if (_current_animation_name.empty()) return 0;

    std::vector<unsigned int> texture_indeces = _animation_group->at(_current_animation_name).texture_indeces;
    return texture_indeces[_current_animation_frame];
}

bool Entity::isMirrored() const {
    return _h_mirror;
}

void Entity::updateAnimationFrame() {
    std::vector<unsigned int> texture_indeces = _animation_group->at(_current_animation_name).texture_indeces;

    notifyObservers(texture_indeces[_current_animation_frame], _h_mirror);
}

void Entity::startAnimation(const std::string &animation_name, bool mirrored) {
    _current_animation_name = animation_name;
    _h_mirror = mirrored;
    _current_animation_frame = 0;
    _current_animation_time = 0;

    updateAnimationFrame();
}

void Entity::advanceAnimation() {
    if (_current_animation_name.empty()) {
        return;
    }

    float framerate = _animation_group->at(_current_animation_name).framerate;
    _current_animation_time += framerate;

    if (_current_animation_time >= 1 || framerate == 0) {
        if (_current_animation_frame + 1 < _animation_group->at(_current_animation_name).texture_indeces.size()) {
            _current_animation_frame += 1;
            _current_animation_time -= 1;
            updateAnimationFrame();
        } else if (_animation_group->at(_current_animation_name).loop) {
            _current_animation_frame = 0;
            _current_animation_time -= 1;
            updateAnimationFrame();
        }
    }
}

std::shared_ptr<Hitbox> Entity::getHitbox() {
    return _hitbox;
}

Hitbox Entity::getScreenHitbox() {
    return {_camera->projectCoordCoreToGame(_hitbox->getPosition()),
            _camera->projectSizeCoreToGame(_hitbox->getSize())};
}

void Entity::setHitbox(const Vector2f &position, const Vector2f &size) {
    _hitbox = std::make_shared<Hitbox>(position, size);
}

void Entity::setHitbox(const Hitbox &hitbox) {
    _hitbox = std::make_shared<Hitbox>(hitbox);
}

void Entity::setHitbox(const std::shared_ptr<Hitbox> &hitbox) {
    _hitbox = hitbox;
}

void Entity::setHitboxOffset(const Vector2f &hitbox_offset) {
    _hitbox_offset = hitbox_offset;
    _hitbox->setPosition(_position + _hitbox_offset);
}
