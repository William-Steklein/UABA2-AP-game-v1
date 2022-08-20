#include "EntityTextView.h"

EntityTextView::EntityTextView(std::weak_ptr<Entity> entity) : EntityView(std::move(entity)) {
    if (!_font.loadFromFile("data/fonts/PT_Sans/PTSans-Regular.ttf")) {
        // todo: exception handling
        std::cout << "couldn't load font" << std::endl;
    }

    _text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";

    _text_render.setFont(_font);
    _text_render.setString(_text);
    _text_render.setCharacterSize(100);
    _text_render.setFillColor(sf::Color::Red);
    _text_render.setStyle(sf::Text::Regular);

    sf::FloatRect text_rect = _text_render.getLocalBounds();
//    std::cout << text_rect.width << std::endl;
//    std::cout << text_rect.height << std::endl;
    _text_render.setOrigin(text_rect.left + text_rect.width / 2, text_rect.top + text_rect.height / 2);

    updateText();
}

void EntityTextView::handleEvent() {
    updateText();
}

void EntityTextView::handleEvent(const unsigned int &event, const unsigned int &channel) {

}

sf::Text EntityTextView::getText() const {
    return _text_render;
}

void EntityTextView::updateText() {
    std::shared_ptr<Entity> entity_shared = _entity.lock();
    if (entity_shared) {
        // transform
        Vector2f new_position = entity_shared->getScreenPosition();
        _text_render.setPosition(new_position.x, new_position.y);

        Vector2f entity_size = entity_shared->getScale();
        _text_render.setScale(entity_size.x, entity_size.y);

        _text_render.setRotation(to_degree(entity_shared->getRotation()));
    }
}

void EntityTextView::updateTextWrap(const Vector2f& view_size) {
    std::shared_ptr<Entity> entity_shared = _entity.lock();
    if (entity_shared) {
        sf::FloatRect text_render_rect = _text_render.getLocalBounds();
        std::cout << text_render_rect.width << std::endl;
        std::cout << text_render_rect.height << std::endl;

        if (text_render_rect.width >= entity_shared->getScreenViewSize().x) {
            _text_wrapped = "";

            std::string _text_wrap_buffer;

            for (const char &c: _text) {
                _text_wrap_buffer.push_back(c);
            }

            _text_wrapped = _text_wrap_buffer;
        }

        std::cout << _text_wrapped << std::endl;
    }
}
