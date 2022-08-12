#include "EntityTexAni.h"

#include <utility>

EntityTexAni::EntityTexAni(std::vector<sf::Texture> textures, std::map<std::string, AnimationData> animations)
        : _textures(std::move(textures)), _animations(std::move(animations)) {

}

const std::vector<sf::Texture> &EntityTexAni::getTextures() const {
    return _textures;
}

const sf::Texture &EntityTexAni::getTexture(unsigned int texture_id) const {
    if (texture_id >= _textures.size()) {
        // todo: exception
    }
    return _textures[texture_id];
}

const AnimationData &EntityTexAni::getAnimation(const std::string& animation_name) const {
    return _animations.at(animation_name);
}
