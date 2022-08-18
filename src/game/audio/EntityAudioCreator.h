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
    std::map<std::string, std::shared_ptr<sf::SoundBuffer>> _sound_buffers;
    std::map<std::string, std::shared_ptr<std::string>> _music_files;

    std::vector<std::weak_ptr<EntityAudio>> _entity_audios;

public:
    EntityAudioCreator() = default;

    void loadSound(const std::string &sound_name, const std::string &filename) override;

    void loadMusic(const std::string &music_name, const std::string &filename) override;

    void createEntityAudio(std::shared_ptr<Entity> entity) override;
};


#endif //GAMEENGINE_ENTITYAUDIOCREATOR_H
