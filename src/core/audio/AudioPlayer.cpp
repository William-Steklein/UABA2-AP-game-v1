#include "AudioPlayer.h"

void AudioPlayer::addSound(unsigned int sound_id, const std::string &sound_name) {
    _sound_ids[sound_name] = sound_id;
}

void AudioPlayer::addMusic(unsigned int music_id, const std::string &music_name) {
    _music_ids[music_name] = music_id;
}

unsigned int AudioPlayer::getSoundId(const std::string &sound_name) {
    // todo exception handling

    _current_sound = sound_name;
    return _sound_ids.at(sound_name);
}

unsigned int AudioPlayer::getMusicId(const std::string &music_name) {
    // todo exception handling

    _current_music = music_name;
    return _music_ids.at(music_name);
}

const std::string &AudioPlayer::getCurrentSound() const {
    return _current_sound;
}

const std::string &AudioPlayer::getCurrentMusic() const {
    return _current_music;
}
