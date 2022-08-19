#ifndef GAMEENGINE_ENTITYAUDIOCREATOR_H
#define GAMEENGINE_ENTITYAUDIOCREATOR_H


#include <string>
#include <map>
#include <SFML/Audio.hpp>
#include <memory>
#include "core/audio/IEntityAudioCreator.h"
#include "EntityAudio.h"

class EntityAudioCreator : public IEntityAudioCreator {
private:
    std::vector<std::shared_ptr<sf::SoundBuffer>> _sound_buffers;
    std::vector<std::string> _music_files;

    std::vector<std::weak_ptr<EntityAudio>> _entity_audios;

public:
    EntityAudioCreator() = default;

    unsigned int loadSound(const std::string &filename) override;

    unsigned int loadMusic(const std::string &filename) override;

    void createEntityAudio(std::shared_ptr<Entity> entity) override;
};


#endif //GAMEENGINE_ENTITYAUDIOCREATOR_H
