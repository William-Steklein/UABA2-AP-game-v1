#include <memory>
#include "AudioPlayer.h"

AudioPlayer::AudioPlayer() : _current_volume(100), _max_distance(1) {

}

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

unsigned int AudioPlayer::getCurrentVolume() const {
    return _current_volume;
}

void AudioPlayer::setCurrentVolume(unsigned int currentVolume) {
    _current_volume = currentVolume;
}

const std::shared_ptr<Vector2f> &AudioPlayer::getAudioListenerPosition() const {
    return _audio_listener_position;
}

void AudioPlayer::setAudioListenerPosition(const std::shared_ptr<Vector2f> &audio_listener_position) {
    _audio_listener_position = audio_listener_position;
}

float AudioPlayer::getMaxDistance() const {
    return _max_distance;
}

void AudioPlayer::setMaxDistance(float max_distance) {
    _max_distance = max_distance;
}
