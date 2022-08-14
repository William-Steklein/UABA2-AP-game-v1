#ifndef GAMEENGINE_HITBOX_H
#define GAMEENGINE_HITBOX_H


#include "../math/Vector2f.h"

class Hitbox {
private:
    Vector2f _position;
    Vector2f _size;

public:
    Hitbox() = default;

    Hitbox(const Vector2f &position, const Vector2f &size);

    const Vector2f &getPosition() const;

    void setPosition(const Vector2f &position);

    const Vector2f &getSize() const;

    void setSize(const Vector2f &size);

    bool empty() const;

    bool collides(const Hitbox &other) const;

    Vector2f getDisplacementToCollision(const Hitbox &other) const;
};


#endif //GAMEENGINE_HITBOX_H
