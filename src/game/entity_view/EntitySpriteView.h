#ifndef GAMEENGINE_ENTITYSPRITEVIEW_H
#define GAMEENGINE_ENTITYSPRITEVIEW_H


#include "EntityView.h"
#include <memory>
#include <utility>

class EntitySpriteView : public EntityView {
private:
    sf::Sprite _sprite;

    std::shared_ptr<std::vector<sf::Texture>> _texture_group;
    unsigned int _current_texture;

public:
    EntitySpriteView(std::weak_ptr<Entity> entity, std::shared_ptr<std::vector<sf::Texture>> texture_group);

    void handleEvent() override;

    void handleEvent(const std::string &event, const std::string &channel="") override;

    void setTexture(unsigned int texture_id);

    sf::Sprite getSprite() const;

    void updateSprite();
};


#endif //GAMEENGINE_ENTITYSPRITEVIEW_H
