#ifndef GAMEENGINE_ENTITYVIEW_H
#define GAMEENGINE_ENTITYVIEW_H


#include <memory>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <vector>
#include "core/observer_pattern_interface/IObserver.h"
#include "core/entities/Entity.h"
#include "core/animation/AnimationStateMachine.h"
#include <filesystem>

class EntityView : public IObserver {
private:
    std::weak_ptr<Entity> _entity;
    sf::Sprite _sprite;

    std::vector<sf::Texture> _textures;
    uint _current_texture;
    AnimationStateMachine _animation_state_machine;

public:
    EntityView(std::weak_ptr<Entity> entity, const std::vector<std::string> &texture_files,
               AnimationStateMachine animation_state_machine);

    ~EntityView() = default;

    void handleEvent() override;

    void handleEvent(const std::string &event) override;

    uint addTexture(const std::string &texture_file);

    void setTexture(uint texture_id);

    sf::Sprite getSprite() const;
};


#endif //GAMEENGINE_ENTITYVIEW_H
