#include "AnimationPlayer.h"

#include <utility>

AnimationPlayer::AnimationPlayer(std::string name, std::shared_ptr<std::map<std::string, Animation>> animations)
        : _name(std::move(name)), _animations(std::move(animations)), _horizontal_mirror(false),
          _current_animation_name(""), _current_animation_frame(0), _current_animation_time(0) {

}

const std::string &AnimationPlayer::getName() const {
    return _name;
}

const std::shared_ptr<std::map<std::string, Animation>> &AnimationPlayer::getAnimations() const {
    return _animations;
}

void AnimationPlayer::setAnimations(const std::shared_ptr<std::map<std::string, Animation>> &animations) {
    _animations = animations;
}

void AnimationPlayer::addAnimation(const std::string &animation_name, const Animation &animation) {
    _animations->insert({animation_name, animation});
}

bool AnimationPlayer::isHorizontalMirror() const {
    return _horizontal_mirror;
}

void AnimationPlayer::setHorizontalMirror(bool horizontal_mirror) {
    _horizontal_mirror = horizontal_mirror;
}

const std::string &AnimationPlayer::getCurrentAnimationName() const {
    return _current_animation_name;
}

unsigned int AnimationPlayer::getCurrentTextureIndex() const {
    if (_current_animation_name.empty()) return 0;

    std::vector<unsigned int> texture_indeces = _animations->at(_current_animation_name).texture_indeces;
    return texture_indeces[_current_animation_frame];
}

void AnimationPlayer::startAnimation(const std::string &animation_name) {
    _current_animation_name = animation_name;
    _current_animation_frame = 0;
    _current_animation_time = 0;
}

bool AnimationPlayer::advanceAnimation() {
    if (_current_animation_name.empty()) {
        return false;
    }

    float framerate = _animations->at(_current_animation_name).framerate;
    _current_animation_time += framerate;

    if (_current_animation_time >= 1 || framerate == 0) {
        if (_current_animation_frame + 1 < _animations->at(_current_animation_name).texture_indeces.size()) {
            _current_animation_frame += 1;
            _current_animation_time -= 1;
            return true;
        } else if (_animations->at(_current_animation_name).loop) {
            _current_animation_frame = 0;
            _current_animation_time -= 1;
            return true;
        }
    }

    return false;
}
