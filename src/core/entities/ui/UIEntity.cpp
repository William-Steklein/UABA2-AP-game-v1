#include "UIEntity.h"

UIEntity::UIEntity(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &view_size,
                   AnimationPlayer animation_player, AudioPlayer audio_player, bool static_view)
        : Entity(position, std::move(camera), view_size, std::move(animation_player), std::move(audio_player)),
          _static_view(static_view) {

}

bool UIEntity::isStaticView() const {
    return _static_view;
}

bool UIEntity::isRelativePositioning() const {
    return _relative_positioning;
}

void UIEntity::setRelativePositioning(bool relative_positioning) {
    _relative_positioning = relative_positioning;
}

const std::weak_ptr<Entity> &UIEntity::getParent() const {
    return _parent;
}

void UIEntity::setParent(const std::weak_ptr<Entity> &parent) {
    _parent = parent;
}

bool UIEntity::hasParent() const {
    return !_parent.expired();
}

const std::vector<std::shared_ptr<UIEntity>> &UIEntity::getChildren() const {
    return _children;
}

void UIEntity::setChildren(const std::vector<std::shared_ptr<UIEntity>> &children) {
    _children = children;
}

void UIEntity::addChild(const std::shared_ptr<UIEntity> &child, const std::weak_ptr<Entity> &parent,
                        bool relative_positioning) {
    child->setParent(parent);
    child->_relative_positioning = relative_positioning;
    if (relative_positioning) {
        child->setRelativePosition(child->getPosition());
    }
    _children.push_back(child);
}

bool UIEntity::hasChildren() const {
    return !_children.empty();
}

void UIEntity::update(double t, float dt) {
    Entity::update(t, dt);

    for (const auto &child: _children) {
        child->update(t, dt);
    }
}

void UIEntity::setPosition(const Vector2f &position) {
    for (const auto &child: _children) {
        if (child->_relative_positioning) {
            child->move(position - _position);
        }
    }

    Entity::setPosition(position);
}

void UIEntity::setRelativePosition(const Vector2f &position) {
    if (_relative_positioning && !_parent.expired()) {
        std::shared_ptr<Entity> parent = _parent.lock();
        setPosition(parent->getPosition() + position);
    }
}
