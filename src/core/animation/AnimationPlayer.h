#ifndef GAMEENGINE_ANIMATIONPLAYER_H
#define GAMEENGINE_ANIMATIONPLAYER_H


#include <string>
#include <map>
#include <memory>
#include <utility>
#include "Animation.h"

class AnimationPlayer {
private:
    std::string _name;
    std::shared_ptr<std::map<std::string, Animation>> _animations;
    bool _horizontal_mirror;

    std::string _current_animation_name;
    unsigned int _current_animation_frame;
    float _current_animation_time;

public:
    AnimationPlayer(std::string name = "",
                    std::shared_ptr<std::map<std::string, Animation>> animations =
                    std::make_shared<std::map<std::string, Animation>>());

    const std::string &getName() const;

    const std::shared_ptr<std::map<std::string, Animation>> &getAnimations() const;

    void setAnimations(const std::shared_ptr<std::map<std::string, Animation>> &animations);

    void addAnimation(const std::string &animation_name, const Animation &animation);

    bool isHorizontalMirror() const;

    void setHorizontalMirror(bool horizontal_mirror);

    const std::string &getCurrentAnimationName() const;

    unsigned int getCurrentTextureIndex() const;

    void startAnimation(const std::string &animation_name);

    bool advanceAnimation();
};


#endif //GAMEENGINE_ANIMATIONPLAYER_H
