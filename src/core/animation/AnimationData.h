#ifndef GAMEENGINE_ANIMATIONDATA_H
#define GAMEENGINE_ANIMATIONDATA_H


#include <vector>
#include <utility>

class AnimationData {
private:
    std::vector<unsigned int> _texture_frames;
    // animation frames per physics frame
    float _framerate;
    bool _loop;

public:
    AnimationData(std::vector<unsigned int> texture_frames, float framerate, bool loop=false);

    const std::vector<unsigned int> &getTextureFrames() const;

    float getFramerate() const;

    bool isLoop() const;
};


#endif //GAMEENGINE_ANIMATIONDATA_H
