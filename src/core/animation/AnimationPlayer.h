#ifndef GAMEENGINE_ANIMATIONPLAYER_H
#define GAMEENGINE_ANIMATIONPLAYER_H


#include <vector>
#include <utility>
#include <string>

struct AnimationResource {
    std::vector<std::string> texture_filenames;
    float framerate;
    bool loop;

    AnimationResource(const std::string &texture_filename) {
        texture_filenames = {texture_filename};
        framerate = 0.f;
        loop = true;
    };

    AnimationResource(const std::vector<std::string> &_texture_filenames, float _framerate, bool _loop) {
        texture_filenames = _texture_filenames;
        framerate = _framerate;
        loop = _loop;
    };
};

struct AnimationPlayer {
    std::vector<unsigned int> texture_indeces;
    float framerate;
    bool loop;
};


#endif //GAMEENGINE_ANIMATIONPLAYER_H
