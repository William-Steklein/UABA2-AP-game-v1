#include "EntitySpriteView.h"

EntitySpriteView::EntitySpriteView(std::weak_ptr<Entity> entity, std::shared_ptr<EntityTexAni> entity_texani)
        : EntityView(std::move(entity)), _entity_texani(std::move(entity_texani)), _current_texture(0),
          _current_animation_frame(0), _current_animation("") {
    setTexture(0);
    updateSprite();
}

void EntitySpriteView::handleEvent() {
    updateSprite();
}

void EntitySpriteView::handleEvent(const std::string &event, const std::string &channel) {
    if (channel == "animation") {
        startAnimation(event);
    }
}

void EntitySpriteView::setTexture(unsigned int texture_id) {
    _current_texture = texture_id;

    _sprite.setTexture(_entity_texani->getTexture(_current_texture), true);
    _sprite.setOrigin(static_cast<float>(_sprite.getTextureRect().width) / 2,
                      static_cast<float>(_sprite.getTextureRect().height) / 2);
}

sf::Sprite EntitySpriteView::getSprite() const {
    return _sprite;
}

void EntitySpriteView::updateSprite() {
    std::shared_ptr<Entity> entity_shared = _entity.lock();
    if (entity_shared) {
        // animation
        advanceAnimation();

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

void EntitySpriteView::startAnimation(const std::string &animation) {
    _current_animation = animation;
    _current_animation_frame = -1;
    _current_animation_time = -(_entity_texani->getAnimation(_current_animation).getFramerate());
}

void EntitySpriteView::advanceAnimation() {
    if (_current_animation.empty()) {
        return;
    }

    std::vector<unsigned int> texture_frames = _entity_texani->getAnimation(_current_animation).getTextureFrames();
    float framerate = _entity_texani->getAnimation(_current_animation).getFramerate();
    _current_animation_time += framerate;

    if (_current_animation_frame + 1 < texture_frames.size() && (_current_animation_time >= 1 || framerate == 0)) {
        setTexture(texture_frames[_current_animation_frame + 1]);
        _current_animation_frame += 1;
        _current_animation_time -= 1;
    }
}
