#ifndef GAMEENGINE_CAMERA_H
#define GAMEENGINE_CAMERA_H

#include "math/vector2f.h"
#include "constants.h"
#include "math/math_funcs.h"
#include <cmath>

class Camera {
private:
    Vector2f _position;

    Vector2f _camera_x_Boundaries;
    Vector2f _camera_y_Boundaries;
    Vector2f _game_x_Boundaries;
    Vector2f _game_y_Boundaries;

    bool _is_focused;

public:
    Camera();

    bool getFocused() const;

    void setFocused(bool is_focused);

    void move(const Vector2f &vector);

    void reset();

    Vector2f getPosition() const;

    void setPosition(const Vector2f &position);

    Vector2f getXBounderies() const;

    Vector2f getYBounderies() const;

    void setCameraBounderies(float x_min, float x_max, float y_min, float y_max);

    float getCameraWidth() const;

    float getCameraHeight() const;

    Vector2f getGameXBoundaries() const;

    Vector2f getGameYBoundaries() const;

    void setGameBoundaries(float x_min, float x_max, float y_min, float y_max);

    Vector2f projectCoordinateCoreToGame(const Vector2f &point) const;

    Vector2f projectCoordinateGameToCore(const Vector2f &point) const;

    Vector2f
    projectCoordinateCustomToCore(const Vector2f &point, float x_min, float x_max, float y_min, float y_max) const;

    Vector2f projectSize(const Vector2f &size) const;

    Vector2f projectSize(const Vector2f &size, float x_min, float x_max, float y_min,
                         float y_max) const;
};

#endif // GAMEENGINE_CAMERA_H
