#ifndef GAMEENGINE_ANIMATIONSTATEMACHINE_H
#define GAMEENGINE_ANIMATIONSTATEMACHINE_H


#include <string>
#include <vector>

class AnimationStateMachine {
private:


public:
    AnimationStateMachine();

    void addAnimation(const std::string& name, const std::vector<unsigned int> &frames, unsigned int framerate,
                      bool loop);

    void removeAnimation(const std::string& name);
};


#endif //GAMEENGINE_ANIMATIONSTATEMACHINE_H
