#include "EntitySpriteView.h"

EntitySpriteView::EntitySpriteView(std::weak_ptr<Entity> entity,
                                   std::shared_ptr<std::vector<sf::Texture>> texture_group)
        : EntityView(std::move(entity)), _texture_group(std::move(texture_group)), _current_texture(0) {
    setTexture(0);
    updateSprite();
}

void EntitySpriteView::handleEvent() {
    updateSprite();
}

void EntitySpriteView::handleEvent(const std::string &event, const std::string &channel) {

}

void EntitySpriteView::setTexture(unsigned int texture_id) {
    _current_texture = texture_id;

    _sprite.setTexture(_texture_group->at(_current_texture), true);
    _sprite.setOrigin(static_cast<float>(_sprite.getTextureRect().width) / 2,
                      static_cast<float>(_sprite.getTextureRect().height) / 2);
}

sf::Sprite EntitySpriteView::getSprite() const {
    return _sprite;
}

void EntitySpriteView::updateSprite() {
    std::shared_ptr<Entity> entity_shared = _entity.lock();
    if (entity_shared) {
        // transform
        Vector2f new_position = entity_shared->getGamePosition();
        _sprite.setPosition(new_position.x, new_position.y);

        auto texture_size = _sprite.getTexture()->getSize();
        Vector2f entity_size = entity_shared->getScale();

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
