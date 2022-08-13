#ifndef GAMEENGINE_ENTITYTEXTVIEW_H
#define GAMEENGINE_ENTITYTEXTVIEW_H


#include <SFML/Graphics/Text.hpp>
#include "EntityView.h"

class EntityTextView : public EntityView {
private:
    sf::Text _text;

public:
    EntityTextView(std::weak_ptr<Entity> entity);

    void handleEvent() override;

    void handleEvent(const unsigned int &event, const unsigned int &channel) override;

    sf::Text getText() const;
};


#endif //GAMEENGINE_ENTITYTEXTVIEW_H
