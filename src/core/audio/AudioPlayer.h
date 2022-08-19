#ifndef GAMEENGINE_AUDIOPLAYER_H
#define GAMEENGINE_AUDIOPLAYER_H


#include <map>
#include <string>

class AudioPlayer {
private:
    std::map<std::string, unsigned int> _sound_ids;
    std::map<std::string, unsigned int> _music_ids;

    std::string _current_sound;
    std::string _current_music;

public:
    AudioPlayer() = default;

    void addSound(unsigned int sound_id, const std::string& sound_name);

    void addMusic(unsigned int music_id, const std::string& music_name);

    unsigned int getSoundId(const std::string& sound_name);

    unsigned int getMusicId(const std::string& music_name);

    const std::string &getCurrentSound() const;

    const std::string &getCurrentMusic() const;
};


#endif //GAMEENGINE_AUDIOPLAYER_H
