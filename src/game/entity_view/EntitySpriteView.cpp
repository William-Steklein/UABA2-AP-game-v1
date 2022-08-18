#include "EntitySpriteView.h"

EntitySpriteView::EntitySpriteView(std::weak_ptr<Entity> entity,
                                   std::shared_ptr<std::vector<sf::Texture>> texture_group)
        : EntityView(std::move(entity)), _h_mirror(false), _texture_group(std::move(texture_group)),
          _current_texture_index(0) {
    std::shared_ptr<Entity> shared_entity = _entity.lock();
    setTexture(shared_entity->getCurrentTextureIndex(), shared_entity->isHorizontalMirror());
    updateSprite();
}

void EntitySpriteView::handleEvent() {
    updateSprite();
}

void EntitySpriteView::handleEvent(const unsigned int &event, const unsigned int &channel) {
    if (channel == 0) {
        setTexture(event);
    } else if (channel == 1) {
        setTexture(event, true);
    }
}

void EntitySpriteView::setTexture(unsigned int texture_index, bool h_mirror) {
    _h_mirror = h_mirror;
    _current_texture_index = texture_index;

    _sprite.setTexture(_texture_group->at(_current_texture_index), true);
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
        Vector2f new_position = entity_shared->getScreenPosition();
        _sprite.setPosition(new_position.x, new_position.y);

        auto texture_size = _sprite.getTexture()->getSize();
        Vector2f entity_size = entity_shared->getScale();

        float x_scale_factor = entity_shared->getScreenViewSize().x /
                               static_cast<float>(texture_size.x) *
                               entity_size.x;

        float y_scale_factor = entity_shared->getScreenViewSize().y /
                               static_cast<float>(texture_size.y) *
                               entity_size.y;

        _sprite.setScale(_h_mirror ? -x_scale_factor : x_scale_factor, y_scale_factor);

        _sprite.setRotation(to_degree(entity_shared->getRotation()));
    }
}
