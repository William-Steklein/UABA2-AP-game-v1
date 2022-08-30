#ifndef GAMEENGINE_HITBOX_H
#define GAMEENGINE_HITBOX_H


#include "../math/Vector2f.h"
#include <memory>

class Hitbox {
private:
    Vector2f _original_position;
    Vector2f _offset;
    Vector2f _position;

    Vector2f _size;

public:
    Hitbox() = default;

    Hitbox(const Vector2f &position, const Vector2f &size, const Vector2f &offset = {0, 0});

    const Vector2f &getPosition() const;

    void setPosition(const Vector2f &position);

    const Vector2f &getSize() const;

    void setSize(const Vector2f &size);

    const Vector2f &getOffset() const;

    void setOffset(const Vector2f &offset);

    void scale(const Vector2f &scale);

    bool empty() const;

    bool collides(const Hitbox &other) const;

    bool collides(const Vector2f &point) const;

    Vector2f getDisplacementToCollision(const Hitbox &other) const;
};


#endif //GAMEENGINE_HITBOX_H
