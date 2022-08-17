#ifndef GAMEENGINE_CAMERA_H
#define GAMEENGINE_CAMERA_H

#include <cmath>
#include "math/Vector2f.h"
#include "math/math_funcs.h"
#include "constants/constants.h"

class Camera {
private:
    Vector2f _position;
    Vector2f _camera_x_boundaries;
    Vector2f _camera_y_boundaries;

    Vector2f _screen_x_boundaries;
    Vector2f _screen_y_boundaries;

    Vector2f _aspect_ratio;
    Vector2f _subscreen_x_boundaries;
    Vector2f _subscreen_y_boundaries;

public:
    Camera(float x_min, float x_max, float y_min, float y_max);

    Vector2f getPosition() const;

    void setPosition(const Vector2f &position);

    void move(const Vector2f &vector);

    void reset();

    Vector2f getXBounderies() const;

    Vector2f getYBounderies() const;

    void setBounderies(float x_min, float x_max, float y_min, float y_max);

    Vector2f getScreenXBoundaries() const;

    Vector2f getScreenYBoundaries() const;

    void setScreenBoundaries(float x_min, float x_max, float y_min, float y_max);

    Vector2f getSubscreenXBoundaries() const;

    Vector2f getSubscreenYBoundaries() const;

    float getWidth() const;

    float getHeight() const;

    float getScreenWidth() const;

    float getScreenHeight() const;

    float getSubscreenWidth() const;

    float getSubscreenHeight() const;

    void updateSubscreenResolution();

    bool isSidescreenHorizontal() const;

    Vector2f projectCoordCoreToGame(const Vector2f &point) const;

    Vector2f projectCoordScreenToCore(const Vector2f &point) const;

    Vector2f projectCoordSubscreenToCore(const Vector2f &point) const;

    Vector2f projectSizeCoreToGame(const Vector2f &size) const;
};

#endif // GAMEENGINE_CAMERA_H
