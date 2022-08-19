#include "AudioPlayer.h"

AudioPlayer::AudioPlayer() {

}

void AudioPlayer::addSound(unsigned int sound_id, const std::string &sound_name) {
    _sound_ids[sound_name] = sound_id;
}

void AudioPlayer::addMusic(unsigned int music_id, const std::string &music_name) {
    _music_ids[music_name] = music_id;
}

unsigned int AudioPlayer::getSoundId(const std::string &sound_name) const {
    // todo exception handling
    return _sound_ids.at(sound_name);
}

unsigned int AudioPlayer::getMusicId(const std::string &music_name) const {
    // todo exception handling
    return _music_ids.at(music_name);
}
