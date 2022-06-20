#include "Camera.h"

Camera::Camera()
        : _camera_x_Boundaries(constants::camera_view_x_min, constants::camera_view_x_max),
          _camera_y_Boundaries(constants::camera_view_y_min, constants::camera_view_y_max) {
    _position = {(_camera_x_Boundaries.y + _camera_x_Boundaries.x) / 2,
                 (_camera_y_Boundaries.y + _camera_y_Boundaries.x) / 2};
}

void Camera::move(const Vector2f &vector) {
    _camera_x_Boundaries += vector.x;
    _camera_y_Boundaries += vector.y;
    _position += vector;
}

void Camera::reset() {
    _camera_x_Boundaries = {constants::camera_view_x_min, constants::camera_view_x_max};
    _camera_y_Boundaries = {constants::camera_view_y_min, constants::camera_view_y_max};
}

Vector2f Camera::getPosition() const { return _position; }

void Camera::setPosition(const Vector2f &position) { move(position - _position); }

Vector2f Camera::getXBounderies() const { return _camera_x_Boundaries; }

Vector2f Camera::getYBounderies() const { return _camera_y_Boundaries; }

void Camera::setCameraBounderies(float x_min, float x_max, float y_min, float y_max) {
    _camera_x_Boundaries = {x_min, x_max};
    _camera_y_Boundaries = {y_min, y_max};
}

float Camera::getCameraWidth() const { return _camera_x_Boundaries.y - _camera_x_Boundaries.x; }

float Camera::getCameraHeight() const { return _camera_y_Boundaries.y - _camera_y_Boundaries.x; }

Vector2f Camera::getGameXBoundaries() const { return _game_x_Boundaries; }

Vector2f Camera::getGameYBoundaries() const { return _game_y_Boundaries; }

void Camera::setGameBoundaries(float x_min, float x_max, float y_min, float y_max) {
    _game_x_Boundaries = {x_min, x_max};
    _game_y_Boundaries = {y_min, y_max};
}

Vector2f Camera::projectCoordinateCoreToGame(const Vector2f &point) const {
    Vector2f new_point;

    float alpha_x{0};
    float alpha_y{0};

    // check if the limits are valid and calculate alpha value
    if (_camera_x_Boundaries.y - _camera_x_Boundaries.x != 0)
        alpha_x = (point.x - _camera_x_Boundaries.x) / (_camera_x_Boundaries.y - _camera_x_Boundaries.x);
    else
        alpha_x = 0;

    if (_camera_y_Boundaries.y - _camera_y_Boundaries.x != 0)
        alpha_y = (point.y - _camera_y_Boundaries.x) / (_camera_y_Boundaries.y - _camera_y_Boundaries.x);
    else
        alpha_y = 0;

    // linear interpolation of coordinate
    new_point = {lerp(_game_x_Boundaries.x, _game_x_Boundaries.y, alpha_x),
                 lerp(_game_y_Boundaries.x, _game_y_Boundaries.y, alpha_y)};

    return new_point;
}

Vector2f Camera::projectCoordinateGameToCore(const Vector2f &point) const {
    Vector2f new_point;

    float alpha_x{0};
    float alpha_y{0};

    // check if the limits are valid and calculate alpha value
    if (_game_x_Boundaries.y - _game_x_Boundaries.x != 0)
        alpha_x = (point.x - _game_x_Boundaries.x) /
                  (_game_x_Boundaries.y - _game_x_Boundaries.x);
    else
        alpha_x = 0;

    if (_game_y_Boundaries.y - _game_y_Boundaries.x != 0)
        alpha_y = (point.y - _game_y_Boundaries.x) /
                  (_game_y_Boundaries.y - _game_y_Boundaries.x);
    else
        alpha_y = 0;

    // linear interpolation of coordinate
    new_point = {lerp(_camera_x_Boundaries.x, _camera_x_Boundaries.y, alpha_x),
                 lerp(_camera_y_Boundaries.x, _camera_y_Boundaries.y, alpha_y)};

    return new_point;
}

Vector2f
Camera::projectCoordinateCustomToCore(const Vector2f &point, float x_min, float x_max, float y_min, float y_max) const {
    Vector2f new_point;

    float alpha_x{0};
    float alpha_y{0};

    // check if the limits are valid and calculate alpha value
    if (x_max - x_min != 0)
        alpha_x = (point.x - x_min) / (x_max - x_min);
    else
        alpha_x = 0;

    if (y_max - y_min != 0)
        alpha_y = (point.y - y_min) / (y_max - y_min);
    else
        alpha_y = 0;

    // linear interpolation of coordinate
    new_point = {lerp(_camera_x_Boundaries.x, _camera_x_Boundaries.y, alpha_x),
                 lerp(_camera_y_Boundaries.x, _camera_y_Boundaries.y, alpha_y)};

    return new_point;
}

Vector2f Camera::projectSize(const Vector2f &size) const {
    Vector2f new_size;

    new_size.x = std::abs(((_game_x_Boundaries.y - _game_x_Boundaries.x) /
                           (_camera_x_Boundaries.y - _camera_x_Boundaries.x))) * size.x;

    new_size.y = std::abs(((_game_y_Boundaries.y - _game_y_Boundaries.x) /
                           (_camera_y_Boundaries.y - _camera_y_Boundaries.x))) * size.y;

    return new_size;
}

Vector2f Camera::projectSize(const Vector2f &size, float x_min, float x_max, float y_min, float y_max) const {
    Vector2f new_size;

    new_size.x = std::abs((_camera_x_Boundaries.y - _camera_x_Boundaries.x) / (x_max - x_min)) * size.x;

    new_size.y = std::abs((_camera_y_Boundaries.y - _camera_y_Boundaries.x) / (y_max - y_min)) * size.y;

    return new_size;
}
