#include "Camera.h"

Core::Camera::Camera()
        : _camera_x_Boundaries(CoreConstants::camera_view_x_min, CoreConstants::camera_view_x_max),
          _camera_y_Boundaries(CoreConstants::camera_view_y_min, CoreConstants::camera_view_y_max) {
    _position = {(_camera_x_Boundaries.y + _camera_x_Boundaries.x) / 2,
                 (_camera_y_Boundaries.y + _camera_y_Boundaries.x) / 2};
}

bool Core::Camera::getFocused() const {
    return _is_focused;
}

void Core::Camera::setFocused(bool is_focused) { _is_focused = is_focused; }

void Core::Camera::move(const Core::Vector2f &vector) {
    _camera_x_Boundaries += vector.x;
    _camera_y_Boundaries += vector.y;
    _position += vector;
}

void Core::Camera::reset() {
    _camera_x_Boundaries = {CoreConstants::camera_view_x_min, CoreConstants::camera_view_x_max};
    _camera_y_Boundaries = {CoreConstants::camera_view_y_min, CoreConstants::camera_view_y_max};
}

Core::Vector2f Core::Camera::getPosition() const { return _position; }

void Core::Camera::setPosition(const Core::Vector2f &position) { move(position - _position); }

Core::Vector2f Core::Camera::getXBoundaries() const { return _camera_x_Boundaries; }

Core::Vector2f Core::Camera::getYBoundaries() const { return _camera_y_Boundaries; }

void Core::Camera::setCameraBoundaries(float x_min, float x_max, float y_min, float y_max) {
    _camera_x_Boundaries = {x_min, x_max};
    _camera_y_Boundaries = {y_min, y_max};
}

float Core::Camera::getCamerawidth() const { return _camera_x_Boundaries.y - _camera_x_Boundaries.x; }

float Core::Camera::getCameraheight() const { return _camera_y_Boundaries.y - _camera_y_Boundaries.x; }

Core::Vector2f Core::Camera::getRepresentationXBoundaries() const { return _representation_x_Boundaries; }

Core::Vector2f Core::Camera::getRepresentationYBoundaries() const { return _representation_y_Boundaries; }

void Core::Camera::setRepresentationBoundaries(float x_min, float x_max, float y_min, float y_max) {
    _representation_x_Boundaries = {x_min, x_max};
    _representation_y_Boundaries = {y_min, y_max};
}

Core::Vector2f Core::Camera::projectCoordinateWorldToRepresentation(const Core::Vector2f &point) const {
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
    new_point = {CoreUtils::lerp(_representation_x_Boundaries.x, _representation_x_Boundaries.y, alpha_x),
                 CoreUtils::lerp(_representation_y_Boundaries.x, _representation_y_Boundaries.y, alpha_y)};

    return new_point;
}

Core::Vector2f Core::Camera::projectCoordinateRepresentationToWorld(const Vector2f &point) const {
    Vector2f new_point;

    float alpha_x{0};
    float alpha_y{0};

    // check if the limits are valid and calculate alpha value
    if (_representation_x_Boundaries.y - _representation_x_Boundaries.x != 0)
        alpha_x = (point.x - _representation_x_Boundaries.x) /
                  (_representation_x_Boundaries.y - _representation_x_Boundaries.x);
    else
        alpha_x = 0;
    if (_representation_y_Boundaries.y - _representation_y_Boundaries.x != 0)
        alpha_y = (point.y - _representation_y_Boundaries.x) /
                  (_representation_y_Boundaries.y - _representation_y_Boundaries.x);
    else
        alpha_y = 0;

    // linear interpolation of coordinate
    new_point = {CoreUtils::lerp(_camera_x_Boundaries.x, _camera_x_Boundaries.y, alpha_x),
                 CoreUtils::lerp(_camera_y_Boundaries.x, _camera_y_Boundaries.y, alpha_y)};

    return new_point;
}

Core::Vector2f
Core::Camera::projectCoordinateCustomToWorld(const Vector2f &point, float x_min, float x_max, float y_min,
                                             float y_max) const {
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
    new_point = {CoreUtils::lerp(_camera_x_Boundaries.x, _camera_x_Boundaries.y, alpha_x),
                 CoreUtils::lerp(_camera_y_Boundaries.x, _camera_y_Boundaries.y, alpha_y)};
    //        new_point.y -= _camera_y_Boundaries.y/2 ;
    return new_point;
}

Core::Vector2f Core::Camera::projectSize(const Core::Vector2f &size) const {
    Vector2f new_size;

    new_size.x = std::abs(((_representation_x_Boundaries.y - _representation_x_Boundaries.x) /
                           (_camera_x_Boundaries.y - _camera_x_Boundaries.x))) *
                 size.x;

    new_size.y = std::abs(((_representation_y_Boundaries.y - _representation_y_Boundaries.x) /
                           (_camera_y_Boundaries.y - _camera_y_Boundaries.x))) *
                 size.y;

    return new_size;
}

Core::Vector2f Core::Camera::projectSize(const Core::Vector2f &size, float x_min, float x_max, float y_min,
                                         float y_max) const {
    Vector2f new_size;

    new_size.x = std::abs((_camera_x_Boundaries.y - _camera_x_Boundaries.x) / (x_max - x_min)) * size.x;

    new_size.y = std::abs((_camera_y_Boundaries.y - _camera_y_Boundaries.x) / (y_max - y_min)) * size.y;

    return new_size;
}
