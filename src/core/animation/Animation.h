#ifndef GAMEENGINE_ANIMATION_H
#define GAMEENGINE_ANIMATION_H


#include <vector>
#include <utility>
#include <string>

struct AnimationData {
    std::vector<std::string> texture_filenames;
    float framerate;
    bool loop;
};

struct Animation {
    std::vector<unsigned int> texture_indeces;
    float framerate;
    bool loop;
};


#endif //GAMEENGINE_ANIMATION_H
