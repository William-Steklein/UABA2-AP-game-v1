#ifndef GAMEENGINE_ENTITYSPRITEVIEW_H
#define GAMEENGINE_ENTITYSPRITEVIEW_H


#include "EntityView.h"
#include "EntityTexAni.h"
#include <memory>
#include <utility>

class EntitySpriteView : public EntityView {
private:
    sf::Sprite _sprite;

    std::shared_ptr<EntityTexAni> _entity_texani;
    unsigned int _current_texture;
    std::string _current_animation;
    unsigned int _current_animation_frame;
    float _current_animation_time;

public:
    EntitySpriteView(std::weak_ptr<Entity> entity, std::shared_ptr<EntityTexAni> entity_texani);

    void handleEvent() override;

    void handleEvent(const std::string &event, const std::string &channel="") override;

    void setTexture(unsigned int texture_id);

    sf::Sprite getSprite() const;

    void updateSprite();

    void startAnimation(const std::string &animation);

    void advanceAnimation();
};


#endif //GAMEENGINE_ENTITYSPRITEVIEW_H
