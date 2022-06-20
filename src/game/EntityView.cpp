#include "EntityView.h"

EntityView::EntityView(std::weak_ptr<Entity> entity, const std::vector<std::string> &texture_files,
                       AnimationStateMachine animation_state_machine)
        : _entity(std::move(entity)), _animation_state_machine(animation_state_machine), _current_texture(0) {

    for (const auto &texture_file: texture_files) {
        addTexture(texture_file);
    }

    setTexture(0);
}

void EntityView::handleEvent() {
    std::shared_ptr<Entity> entity_shared = _entity.lock();
    if (entity_shared) {
        Vector2f new_position = entity_shared->getGamePosition();
        _sprite.setPosition(new_position.x, new_position.y);

        float x_scale_factor = entity_shared->getGameViewSize().x /
                               static_cast<float>(_textures[_current_texture].getSize().x) *
                               entity_shared->getScale().x;

        float y_scale_factor = entity_shared->getGameViewSize().y /
                               static_cast<float>(_textures[_current_texture].getSize().y) *
                               entity_shared->getScale().y;

        _sprite.setScale(x_scale_factor, y_scale_factor);
    }
}

void EntityView::handleEvent(const std::string &event) {

}

uint EntityView::addTexture(const std::string &texture_file) {
    sf::Texture new_texture;
    if (!new_texture.loadFromFile(texture_file)) {
        std::cerr << "Couldn't load the texture!" << std::endl;
        return 0;
    }

    _textures.push_back(new_texture);

    return _textures.size() - 1;
}

void EntityView::setTexture(uint texture_id) {
    if (texture_id + 1 > _textures.size())
        return;
    _current_texture = texture_id;

    _sprite.setTexture(_textures[texture_id]);
    _sprite.setOrigin(static_cast<float>(_sprite.getTextureRect().width) / 2,
                      static_cast<float>(_sprite.getTextureRect().height) / 2);
}

sf::Sprite EntityView::getSprite() const {
    return _sprite;
}


