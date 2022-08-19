#include "EntityAudio.h"

EntityAudio::EntityAudio(std::weak_ptr<Entity> entity, std::vector<std::shared_ptr<sf::SoundBuffer>> sound_buffers,
                         std::vector<std::string> music_files) :
        _entity(std::move(entity)), _sound_buffers(std::move(sound_buffers)), _music_files(std::move(music_files)),
        _loop(false), _finish(false) {

}

void EntityAudio::handleEvent() {

}

void EntityAudio::handleEvent(const unsigned int &event, const unsigned int &channel) {
    if (channel == 3) {
        playSound(event);
    } else if (channel == 4) {
        playMusic(event);
    } else if (channel == 5) {
        _finish = event != 0;
    } else if (channel == 6) {
        _loop = event != 0;
    } else if (channel == 7) {
        if (event == 0) {
            _sound.stop();
        } else {
            _music.stop();
        }
    } else if (channel == 8) {
        std::cout << event << std::endl;
        setVolume(event);
    }
}

void EntityAudio::playSound(unsigned int sound_id) {
    if (_sound.getStatus() == 2 && _finish) return;

    _sound.setBuffer(*_sound_buffers[sound_id]);
    _sound.setLoop(_loop);
    _sound.play();
}

void EntityAudio::playMusic(unsigned int music_id) {
    if (_music.getStatus() == 2 && _finish) return;

    if (!_music.openFromFile(_music_files[music_id]))
        return; // todo: exception

    _music.setLoop(_loop);
    _music.play();
}

void EntityAudio::setVolume(unsigned int volume) {
    _sound.setVolume(static_cast<float>(volume));
    _music.setVolume(static_cast<float>(volume));
}
