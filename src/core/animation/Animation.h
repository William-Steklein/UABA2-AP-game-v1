#ifndef GAMEENGINE_ANIMATION_H
#define GAMEENGINE_ANIMATION_H


#include <vector>
#include <utility>
#include <string>

struct AnimationData {
    std::vector<std::string> texture_filenames;
    float framerate;
    bool loop;

    AnimationData(const std::string &texture_filename) {
        texture_filenames = {texture_filename};
        framerate = 0.f;
        loop = true;
    };

    AnimationData(const std::vector<std::string> &_texture_filenames, float _framerate, bool _loop) {
        texture_filenames = _texture_filenames;
        framerate = _framerate;
        loop = _loop;
    };
};

struct Animation {
    std::vector<unsigned int> texture_indeces;
    float framerate;
    bool loop;
};


#endif //GAMEENGINE_ANIMATION_H
