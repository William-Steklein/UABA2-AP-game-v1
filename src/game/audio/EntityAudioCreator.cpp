#include "EntityAudioCreator.h"

unsigned int EntityAudioCreator::loadSound(const std::string &filename) {
    std::shared_ptr<sf::SoundBuffer> new_sound_buffer = std::make_shared<sf::SoundBuffer>();
    if (!new_sound_buffer->loadFromFile(filename)) {
        std::cout << "couldn't load sound from file" << std::endl;
        // todo exception
    }

    _sound_buffers.push_back(new_sound_buffer);

    return _sound_buffers.size() - 1;
}

unsigned int EntityAudioCreator::loadMusic(const std::string &filename) {
    _music_files.push_back(filename);

    return _music_files.size() - 1;
}

void EntityAudioCreator::createEntityAudio(std::shared_ptr<Entity> entity) {
    std::shared_ptr<EntityAudio> new_entity_audio(new EntityAudio(entity, _sound_buffers, _music_files));
    std::weak_ptr<EntityAudio> new_entity_audio_weak = new_entity_audio;

    _entity_audios.push_back(new_entity_audio_weak);

    entity->addObserver(new_entity_audio);

    entity->replayAudio();
}
