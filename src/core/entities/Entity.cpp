#include "Entity.h"

Entity::Entity(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &view_size,
               std::shared_ptr<std::map<std::string, Animation>> animation_group)
        : _position(position), _scale({1, 1}), _rotation(0), _camera(std::move(camera)), _view_size(view_size),
          _animation_group(std::move(animation_group)), _current_animation_name(""), _h_mirror(false),
          _current_animation_frame(0), _current_animation_time(0) {

}

void Entity::update(double t, float dt) {
    advanceAnimation();
    notifyObservers();
}

Vector2f Entity::getViewSize() const {
    return _view_size;
}

Vector2f Entity::getGameViewSize() const {
    return _camera->projectSizeCoreToGame(_view_size);
}

void Entity::setViewSize(const Vector2f &view_size) {
    _view_size = view_size;
}

Vector2f Entity::getPosition() const {
    return _position;
}

Vector2f Entity::getGamePosition() const {
    return _camera->projectCoordCoreToGame(_position);
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
