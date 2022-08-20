#ifndef GAMEENGINE_ENTITYTEXTVIEW_H
#define GAMEENGINE_ENTITYTEXTVIEW_H


#include <SFML/Graphics/Text.hpp>
#include "EntityView.h"

class EntityTextView : public EntityView {
private:
    sf::Font _font;
    sf::Text _text_render;

    std::string _text;
    std::string _text_wrapped;

public:
    EntityTextView(std::weak_ptr<Entity> entity);

    void handleEvent() override;

    void handleEvent(const unsigned int &event, const unsigned int &channel) override;

    sf::Text getText() const;

    void updateText();

    void updateTextWrap(const Vector2f& view_size);
};


#endif //GAMEENGINE_ENTITYTEXTVIEW_H
