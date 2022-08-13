#ifndef GAMEENGINE_ENTITYSPRITEVIEW_H
#define GAMEENGINE_ENTITYSPRITEVIEW_H


#include "EntityView.h"
#include <memory>
#include <utility>

class EntitySpriteView : public EntityView {
private:
    sf::Sprite _sprite;
    bool _h_mirror;

    std::shared_ptr<std::vector<sf::Texture>> _texture_group;
    unsigned int _current_texture_index;

public:
    EntitySpriteView(std::weak_ptr<Entity> entity, std::shared_ptr<std::vector<sf::Texture>> texture_group);

    void handleEvent() override;

    void handleEvent(const unsigned int &event, const unsigned int &channel) override;

    void setTexture(unsigned int texture_index, bool h_mirror=false);

    sf::Sprite getSprite() const;

    void updateSprite();
};


#endif //GAMEENGINE_ENTITYSPRITEVIEW_H
