#ifndef GAMEENGINE_ENTITYSPRITEVIEW_H
#define GAMEENGINE_ENTITYSPRITEVIEW_H


#include "EntityView.h"
#include <memory>

class EntitySpriteView : public EntityView {
private:
    sf::Sprite _sprite;

    std::vector<sf::Texture> _textures;
    unsigned int _current_texture;
    AnimationStateMachine _animation_state_machine;

public:
    EntitySpriteView(std::weak_ptr<Entity> entity,
                     const std::vector<std::string> &texture_files,
                     AnimationStateMachine animation_state_machine);

    void handleEvent() override;

    void handleEvent(const std::string &event) override;

    unsigned int addTexture(const std::string &texture_file);

    void setTexture(unsigned int texture_id);

    sf::Sprite getSprite() const;

    void updateSprite();
};


#endif //GAMEENGINE_ENTITYSPRITEVIEW_H
