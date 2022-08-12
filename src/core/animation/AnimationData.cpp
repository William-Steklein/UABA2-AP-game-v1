#include "AnimationData.h"

AnimationData::AnimationData(std::vector<unsigned int> texture_frames, float framerate, bool loop)
        : _texture_frames(std::move(texture_frames)), _framerate(framerate), _loop(loop) {

}

const std::vector<unsigned int> &AnimationData::getTextureFrames() const {
    return _texture_frames;
}

float AnimationData::getFramerate() const {
    return _framerate;
}

bool AnimationData::isLoop() const {
    return _loop;
}
