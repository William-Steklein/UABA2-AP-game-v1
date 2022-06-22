#include "EntityTextView.h"

EntityTextView::EntityTextView(std::weak_ptr<Entity> entity) : EntityView(std::move(entity)) {

}

void EntityTextView::handleEvent() {

}

void EntityTextView::handleEvent(const std::string &event) {

}

sf::Text EntityTextView::getText() const {
    return _text;
}