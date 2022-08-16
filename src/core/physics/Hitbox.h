#ifndef GAMEENGINE_HITBOX_H
#define GAMEENGINE_HITBOX_H


#include "../math/Vector2f.h"

class Hitbox {
private:
    Vector2f _position;
    Vector2f _original_position;
    Vector2f _scale;

    Vector2f _size;
    Vector2f _original_size;

    Vector2f _offset;
    Vector2f _original_offset;

public:
    Hitbox() = default;

    Hitbox(const Vector2f &position, const Vector2f &size, const Vector2f &offset={0, 0});

    const Vector2f &getPosition() const;

    void setPosition(const Vector2f &position);

    const Vector2f &getScale() const;

    void setScale(const Vector2f &scale);

    const Vector2f &getSize() const;

    void setSize(const Vector2f &size);

    const Vector2f &getOffset() const;

    void setOffset(const Vector2f &offset);

    bool empty() const;

    bool collides(const Hitbox &other) const;

    Vector2f getDisplacementToCollision(const Hitbox &other) const;
};


#endif //GAMEENGINE_HITBOX_H
