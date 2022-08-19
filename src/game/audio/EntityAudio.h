#ifndef GAMEENGINE_ENTITYAUDIO_H
#define GAMEENGINE_ENTITYAUDIO_H


#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/Music.hpp>
#include <memory>
#include <map>
#include <utility>
#include "core/observer-pattern-interface/IObserver.h"
#include "core/entities/Entity.h"

class EntityAudio : public IObserver {
private:
    std::weak_ptr<Entity> _entity;

    std::vector<std::shared_ptr<sf::SoundBuffer>> _sound_buffers;
    std::vector<std::string> _music_files;

    sf::Sound _sound;
    sf::Music _music;

    bool _loop;
    bool _finish;

public:
    EntityAudio(std::weak_ptr<Entity> entity, std::vector<std::shared_ptr<sf::SoundBuffer>> sound_buffers,
                std::vector<std::string> music_files);

    void handleEvent() override;

    void handleEvent(const unsigned int &event, const unsigned int &channel) override;

    void playSound(unsigned int sound_id);

    void playMusic(unsigned int music_id);

    void setVolume(unsigned int volume);
};


#endif //GAMEENGINE_ENTITYAUDIO_H
