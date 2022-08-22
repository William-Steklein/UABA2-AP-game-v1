#ifndef GAMEENGINE_ENTITYTEXTBOXVIEW_H
#define GAMEENGINE_ENTITYTEXTBOXVIEW_H


#include <SFML/Graphics/Text.hpp>
#include "EntityView.h"
#include "core/entities/ui/TextBox.h"

class EntityTextBoxView : public EntityView {
private:
    sf::Font _font;
    sf::Text _text_render;

    std::shared_ptr<std::string> _text;
    std::string _text_wrapped;

    std::weak_ptr<TextBox> _entity_text_box;

public:
    EntityTextBoxView(const std::weak_ptr<TextBox>& entity_text_box);

    void handleEvent() override;

    void handleEvent(const unsigned int &event, const unsigned int &channel) override;

    sf::Text getText() const;

    void updateText();

    void updateTextWrap(const Vector2f& view_size);
};


#endif //GAMEENGINE_ENTITYTEXTBOXVIEW_H
