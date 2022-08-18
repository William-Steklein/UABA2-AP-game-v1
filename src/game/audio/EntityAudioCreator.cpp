#include "EntityAudioCreator.h"

void EntityAudioCreator::loadSound(const std::string &sound_name, const std::string &filename) {
    std::shared_ptr<sf::SoundBuffer> new_sound_buffer = std::make_shared<sf::SoundBuffer>();
    if (!new_sound_buffer->loadFromFile("data/audio/wilhelm_scream.wav")) {
        std::cout << "couldn't load sound from file" << std::endl;
        return;
    }
    _sound_buffers.insert({sound_name, new_sound_buffer});
}

void EntityAudioCreator::loadMusic(const std::string &music_name, const std::string &filename) {

}

void EntityAudioCreator::createEntityAudio(std::shared_ptr<Entity> entity) {
    std::shared_ptr<EntityAudio> new_entity_audio(new EntityAudio(entity, _sound_buffers, _music_files));
    std::weak_ptr<EntityAudio> new_entity_audio_weak = new_entity_audio;

    _entity_audios.push_back(new_entity_audio_weak);

    entity->addObserver(new_entity_audio);
}
