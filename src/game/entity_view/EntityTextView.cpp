#include "EntityTextBoxView.h"

EntityTextBoxView::EntityTextBoxView(const std::weak_ptr<TextBox>& entity_text_box)
        : EntityView(entity_text_box), _entity_text_box(entity_text_box) {
    if (!_font.loadFromFile("data/fonts/PT_Sans/PTSans-Regular.ttf")) {
        // todo: exception handling
        std::cout << "couldn't load font" << std::endl;
    }

    if (!_entity_text_box.expired()) {
        std::shared_ptr<TextBox> entity_text_box_shared = _entity_text_box.lock();
        _text = entity_text_box_shared->getText();
    } else {
        _text = std::make_shared<std::string>("");
    }

    _text_render.setFont(_font);
    _text_render.setString(*_text);
    _text_render.setCharacterSize(30);
    _text_render.setFillColor(sf::Color::Red);
    _text_render.setStyle(sf::Text::Regular);

    std::shared_ptr<Entity> entity_shared = _entity.lock();
    if (entity_shared) {
        updateTextWrap(entity_shared->getScreenViewSize());
    }

    sf::FloatRect text_rect = _text_render.getLocalBounds();
    _text_render.setOrigin(text_rect.left + text_rect.width / 2, text_rect.top + text_rect.height / 2);

    updateText();
}

void EntityTextBoxView::handleEvent() {
    updateText();
}

void EntityTextBoxView::handleEvent(const unsigned int &event, const unsigned int &channel) {

}

sf::Text EntityTextBoxView::getText() const {
    return _text_render;
}

void EntityTextBoxView::updateText() {
    _text_render.setString(*_text);

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

void EntityTextBoxView::updateTextWrap(const Vector2f &view_size) {
    sf::FloatRect text_render_rect = _text_render.getLocalBounds();
    std::cout << text_render_rect.width << std::endl;
    std::cout << text_render_rect.height << std::endl;

    if (text_render_rect.width >= view_size.x) {
        _text_wrapped = "";

        std::string _text_wrap_buffer;
        std::string current_line;
        std::string previous_current_line;
        std::string current_word;
        unsigned int word_count = 0;

        for (const char &c: *_text) {
            if (c != ' ') {
                current_line.push_back(c);
                current_word.push_back(c);
            } else {
                word_count++;

                sf::Text new_text_wrap;
                new_text_wrap.setString(current_line);
                new_text_wrap.setFont(_font);
                new_text_wrap.setCharacterSize(30);

                if (new_text_wrap.getLocalBounds().width > view_size.x) {
                    if (word_count == 1) {
                        _text_wrap_buffer += current_word + "\n";
                        current_line.clear();
                        previous_current_line = current_word;
                        current_word.clear();
                        continue;
                    }
                    _text_wrap_buffer += previous_current_line + "\n";
                    current_line = current_word + " ";
                    previous_current_line = current_word;
                    word_count = 1;

                } else {
                    previous_current_line = current_line;
                    current_line.push_back(' ');
                }

                current_word.clear();
            }
        }

        _text_wrapped = _text_wrap_buffer + current_word;
        _text_render.setString(_text_wrapped);
    }
}
