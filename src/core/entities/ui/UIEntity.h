#ifndef GAMEENGINE_UIENTITY_H
#define GAMEENGINE_UIENTITY_H


#include "../Entity.h"
#include <memory>
#include <utility>

class UIEntity : public Entity {
private:
    bool _static_view;
    bool _relative_positioning;

    std::weak_ptr<UIEntity> _parent;
    std::vector<std::shared_ptr<UIEntity>> _children;

public:
    UIEntity(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &view_size,
             AnimationPlayer animation_player = {}, AudioPlayer audio_player = {}, bool static_view = true);

    ~UIEntity() = default;

    bool isStaticView() const;

    bool isRelativePositioning() const;

    void setRelativePositioning(bool relative_positioning);

    const std::weak_ptr<UIEntity> &getParent() const;

    void setParent(const std::weak_ptr<UIEntity> &parent);

    bool hasParent() const;

    const std::vector<std::shared_ptr<UIEntity>> &getChildren() const;

    void setChildren(const std::vector<std::shared_ptr<UIEntity>> &children);

    void addChild(const std::shared_ptr<UIEntity> &child, const std::weak_ptr<UIEntity> &parent,
                  bool relative_positioning = true);

    bool hasChildren() const;

    void update(double t, float dt) override;

    void setPosition(const Vector2f &position) override;

    void setRelativePosition(const Vector2f &position);
};


#endif //GAMEENGINE_UIENTITY_H
