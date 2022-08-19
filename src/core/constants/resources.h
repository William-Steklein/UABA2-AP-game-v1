#ifndef GAMEENGINE_ANIMATIONDATA_H
#define GAMEENGINE_ANIMATIONDATA_H

#include <map>
#include <string>
#include "../animation/Animation.h"
#include "../audio/AudioResource.h"

extern const std::map<std::string, std::string> texture_data;

extern const std::map<std::string, std::map<std::string, AnimationResource>> animation_groups_data;

extern const std::map<std::string, std::string> audio_sound_data;

extern const std::map<std::string, std::string> audio_music_data;

#endif //GAMEENGINE_ANIMATIONDATA_H
