#ifndef GAMEENGINE_ENTITYTEXANI_H
#define GAMEENGINE_ENTITYTEXANI_H


#include "core/animation/AnimationData.h"
#include <SFML/Graphics/Texture.hpp>
#include <map>
#include <string>

class EntityTexAni {
private:
    std::vector<sf::Texture> _textures;
    std::map<std::string, AnimationData> _animations;

public:
    EntityTexAni(std::vector<sf::Texture> textures, std::map<std::string, AnimationData> animations);

    const std::vector<sf::Texture> &getTextures() const;

    const sf::Texture& getTexture(unsigned int texture_id) const;

    const AnimationData &getAnimation(const std::string& animation_name) const;
};


#endif //GAMEENGINE_ENTITYTEXANI_H
