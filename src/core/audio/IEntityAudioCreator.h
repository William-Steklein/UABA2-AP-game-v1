#ifndef GAMEENGINE_IAUDIOPLAYERCREATOR_H
#define GAMEENGINE_IAUDIOPLAYERCREATOR_H


#include <string>
#include "../entities/Entity.h"

class IEntityAudioCreator {
private:

public:
    virtual void loadSound(const std::string &sound_name, const std::string &filename) = 0;

    virtual void loadMusic(const std::string &music_name, const std::string &filename) = 0;

    virtual void createEntityAudio(std::shared_ptr<Entity> entity) = 0;
};


#endif //GAMEENGINE_IAUDIOPLAYERCREATOR_H
