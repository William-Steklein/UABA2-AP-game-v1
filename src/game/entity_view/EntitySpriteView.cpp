#include "EntitySpriteView.h"
#include <utility>

EntitySpriteView::EntitySpriteView(std::weak_ptr<Entity> entity, const std::vector<std::string> &texture_files,
                                   AnimationStateMachine animation_state_machine)
        : EntityView(std::move(entity)), _animation_state_machine(animation_state_machine),
          _current_texture(0) {
    for (const auto &texture_file: texture_files) {
        addTexture(texture_file);
    }

    setTexture(0);
    updateSprite();
}

void EntitySpriteView::handleEvent() {

}

void EntitySpriteView::handleEvent(const std::string &event) {
    if (event == "update") {
        updateSprite();
    }
}

unsigned int EntitySpriteView::addTexture(const std::string &texture_file) {
    sf::Texture new_texture;
    if (!new_texture.loadFromFile(texture_file)) {
        std::cerr << "Couldn't load the texture!" << std::endl;
        return 0;
    }

    _textures.push_back(new_texture);

    return _textures.size() - 1;
}

void EntitySpriteView::setTexture(unsigned int texture_id) {
    if (texture_id + 1 > _textures.size())
        return;
    _current_texture = texture_id;

    _sprite.setTexture(_textures[texture_id]);
    _sprite.setOrigin(static_cast<float>(_sprite.getTextureRect().width) / 2,
                      static_cast<float>(_sprite.getTextureRect().height) / 2);
}

sf::Sprite EntitySpriteView::getSprite() const {
    return _sprite;
}

void EntitySpriteView::updateSprite() {
    std::shared_ptr<Entity> entity_shared = _entity.lock();
    if (entity_shared) {
        Vector2f new_position = entity_shared->getGamePosition();
        _sprite.setPosition(new_position.x, new_position.y);

        Vector2f entity_size = entity_shared->getScale();
        auto texture_size = _textures[_current_texture].getSize();

        float x_scale_factor = entity_shared->getGameViewSize().x /
                               static_cast<float>(texture_size.x) *
                               entity_size.x;

        float y_scale_factor = entity_shared->getGameViewSize().y /
                               static_cast<float>(texture_size.y) *
                               entity_size.y;

        _sprite.setScale(x_scale_factor, y_scale_factor);

        _sprite.setRotation(to_degree(entity_shared->getRotation()));
    }
}
