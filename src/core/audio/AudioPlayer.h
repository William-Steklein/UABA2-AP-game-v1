#ifndef GAMEENGINE_AUDIOPLAYER_H
#define GAMEENGINE_AUDIOPLAYER_H


#include <map>
#include <string>
#include "../math/Vector2f.h"

class AudioPlayer {
private:
    std::map<std::string, unsigned int> _sound_ids;
    std::map<std::string, unsigned int> _music_ids;

    std::string _current_sound;
    std::string _current_music;

    unsigned int _current_volume;
    std::shared_ptr<Vector2f> _audio_listener_position;
    float _max_distance;

public:
    AudioPlayer();

    void addSound(unsigned int sound_id, const std::string &sound_name);

    void addMusic(unsigned int music_id, const std::string &music_name);

    unsigned int getSoundId(const std::string &sound_name);

    unsigned int getMusicId(const std::string &music_name);

    const std::string &getCurrentSound() const;

    const std::string &getCurrentMusic() const;

    unsigned int getCurrentVolume() const;

    void setCurrentVolume(unsigned int currentVolume);

    const std::shared_ptr<Vector2f> &getAudioListenerPosition() const;

    void setAudioListenerPosition(const std::shared_ptr<Vector2f> &audio_listener_position);

    float getMaxDistance() const;

    void setMaxDistance(float max_distance);
};


#endif //GAMEENGINE_AUDIOPLAYER_H
