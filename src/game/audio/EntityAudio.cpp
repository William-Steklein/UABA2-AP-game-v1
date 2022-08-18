#include "EntityAudio.h"

EntityAudio::EntityAudio(std::weak_ptr<Entity> entity,
                         std::map<std::string, std::shared_ptr<sf::SoundBuffer>> sound_buffers,
                         std::map<std::string, std::shared_ptr<std::string>> music_files) :
        _entity(std::move(entity)), _sound_buffers(std::move(sound_buffers)), _music_files(std::move(music_files)) {

}

void EntityAudio::handleEvent() {

}

void EntityAudio::handleEvent(const unsigned int &event, const unsigned int &channel) {
    if (channel == 3) {
        playSound("scream");
    }
}

void EntityAudio::playSound(const std::string &sound_name) {
    _sound.setBuffer(*_sound_buffers.at(sound_name));
    _sound.play();
}

void EntityAudio::playMusic(const std::string &music_name) {

}
