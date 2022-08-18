#ifndef GAMEENGINE_ANIMATIONDATA_H
#define GAMEENGINE_ANIMATIONDATA_H

#include <map>
#include <string>
#include "../animation/Animation.h"

extern const std::map<std::string, std::string> textures_data;

extern const std::map<std::string, std::map<std::string, AnimationResource>> animation_groups_data;

#endif //GAMEENGINE_ANIMATIONDATA_H
