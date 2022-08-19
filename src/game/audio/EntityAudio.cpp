#include "EntityAudio.h"

EntityAudio::EntityAudio(std::weak_ptr<Entity> entity, std::vector<std::shared_ptr<sf::SoundBuffer>> sound_buffers,
                         std::vector<std::string> music_files) :
        _entity(std::move(entity)), _sound_buffers(std::move(sound_buffers)), _music_files(std::move(music_files)) {

}

void EntityAudio::handleEvent() {

}

void EntityAudio::handleEvent(const unsigned int &event, const unsigned int &channel) {
    if (channel == 3) {
        playSound(event);
    } else if (channel == 4) {
        playMusic(event);
    }
}

void EntityAudio::playSound(unsigned int sound_id) {
    _sound.setBuffer(*_sound_buffers[sound_id]);
    _sound.play();
}

void EntityAudio::playMusic(unsigned int music_id) {
    std::cout << "baba" << std::endl;

    if (!_music.openFromFile(_music_files[music_id]))
        return; // todo: exception
    _music.play();
}
