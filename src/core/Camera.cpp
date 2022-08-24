#include "Camera.h"

Camera::Camera(float x_min, float x_max, float y_min, float y_max)
        : _camera_x_boundaries(constants::camera_view_x_min, constants::camera_view_x_max),
          _camera_y_boundaries(constants::camera_view_y_min, constants::camera_view_y_max),
          _screen_x_boundaries(x_min, x_max), _screen_y_boundaries(y_min, y_max),
          _aspect_ratio(constants::aspect_ratio), _score_amount(0) {
    _position = {(_camera_x_boundaries.y + _camera_x_boundaries.x) / 2,
                 (_camera_y_boundaries.y + _camera_y_boundaries.x) / 2};

    updateSubscreenResolution();
}

Vector2f Camera::getPosition() const { return _position; }

void Camera::setPosition(const Vector2f &position) { move(position - _position); }

void Camera::move(const Vector2f &vector) {
    _camera_x_boundaries += vector.x;
    _camera_y_boundaries += vector.y;
    _position += vector;

    // todo: score constant
    _score_amount += vector.length() * 50;
    if (_score_amount > 1) {
        float score_amount = std::floor(_score_amount);
        _score_amount -= score_amount;

        notifyObservers(static_cast<unsigned int>(score_amount), 25);
    }
}

void Camera::reset() {
    _camera_x_boundaries = {constants::camera_view_x_min, constants::camera_view_x_max};
    _camera_y_boundaries = {constants::camera_view_y_min, constants::camera_view_y_max};
    _position = {(_camera_x_boundaries.y + _camera_x_boundaries.x) / 2,
                 (_camera_y_boundaries.y + _camera_y_boundaries.x) / 2};
    _score_amount = 0;
}

Vector2f Camera::getXBounderies() const { return _camera_x_boundaries; }

Vector2f Camera::getYBounderies() const { return _camera_y_boundaries; }

void Camera::setBounderies(float x_min, float x_max, float y_min, float y_max) {
    _camera_x_boundaries = {x_min, x_max};
    _camera_y_boundaries = {y_min, y_max};
}

Vector2f Camera::getScreenXBoundaries() const { return _screen_x_boundaries; }

Vector2f Camera::getScreenYBoundaries() const { return _screen_y_boundaries; }

void Camera::setScreenBoundaries(float x_min, float x_max, float y_min, float y_max) {
    _screen_x_boundaries = {x_min, x_max};
    _screen_y_boundaries = {y_min, y_max};

    updateSubscreenResolution();
}

Vector2f Camera::getSubscreenXBoundaries() const { return _subscreen_x_boundaries; }

Vector2f Camera::getSubscreenYBoundaries() const { return _subscreen_y_boundaries; }

float Camera::getWidth() const { return _camera_x_boundaries.y - _camera_x_boundaries.x; }

float Camera::getHeight() const { return _camera_y_boundaries.y - _camera_y_boundaries.x; }

float Camera::getScreenWidth() const { return _screen_x_boundaries.y - _screen_x_boundaries.x; }

float Camera::getScreenHeight() const { return _screen_y_boundaries.y - _screen_y_boundaries.x; }

float Camera::getSubscreenWidth() const { return _subscreen_x_boundaries.y - _subscreen_x_boundaries.x; }

float Camera::getSubscreenHeight() const { return _subscreen_y_boundaries.y - _subscreen_y_boundaries.x; }

void Camera::updateSubscreenResolution() {
    Vector2f new_subscreen_resolution;

    // resolution screen
    float r_s = std::abs(getScreenWidth()) / std::abs(getScreenHeight());
    // resolution image (subscreen)
    float r_i = _aspect_ratio.x / _aspect_ratio.y;

    if (r_s > r_i) {
        new_subscreen_resolution = {std::abs(getScreenHeight()) * r_i, std::abs(getScreenHeight())};

        if (_screen_x_boundaries.x < _screen_x_boundaries.y) {
            float middle_point = (_screen_x_boundaries.y - _screen_x_boundaries.x) / 2;
            _subscreen_x_boundaries = {middle_point - new_subscreen_resolution.x / 2,
                                       middle_point + new_subscreen_resolution.x / 2};
        } else {
            float middle_point = (_screen_x_boundaries.x - _screen_x_boundaries.y) / 2;
            _subscreen_x_boundaries = {middle_point + new_subscreen_resolution.x / 2,
                                       middle_point - new_subscreen_resolution.x / 2};
        }

        _subscreen_y_boundaries = _screen_y_boundaries;
    } else {
        new_subscreen_resolution = {getScreenWidth(), getScreenWidth() / r_i};
        _subscreen_x_boundaries = _screen_x_boundaries;

        if (_screen_y_boundaries.x < _screen_y_boundaries.y) {
            float middle_point = (_screen_y_boundaries.y - _screen_y_boundaries.x) / 2;
            _subscreen_y_boundaries = {middle_point - new_subscreen_resolution.y / 2,
                                       middle_point + new_subscreen_resolution.y / 2};
        } else {
            float middle_point = (_screen_y_boundaries.x - _screen_y_boundaries.y) / 2;
            _subscreen_y_boundaries = {middle_point + new_subscreen_resolution.y / 2,
                                       middle_point - new_subscreen_resolution.y / 2};
        }
    }
}

bool Camera::isSidescreenHorizontal() const {
    // resolution screen
    float r_s = std::abs(getScreenWidth()) / std::abs(getScreenHeight());
    // resolution image (subscreen)
    float r_i = _aspect_ratio.x / _aspect_ratio.y;

    return r_s > r_i;
}

Vector2f Camera::projectCoordCoreToGame(const Vector2f &point) const {
    float alpha_x = (point.x - _camera_x_boundaries.x) / getWidth();
    float alpha_y = (point.y - _camera_y_boundaries.x) / getHeight();

    return {lerp(_subscreen_x_boundaries.x, _subscreen_x_boundaries.y, alpha_x),
            lerp(_subscreen_y_boundaries.x, _subscreen_y_boundaries.y, alpha_y)};
}

Vector2f Camera::projectCoordScreenToCore(const Vector2f &point) const {
    float alpha_x = (point.x - _screen_x_boundaries.x) / getScreenWidth();
    float alpha_y = (point.y - _screen_y_boundaries.x) / getScreenHeight();

    return {lerp(_camera_x_boundaries.x, _camera_x_boundaries.y, alpha_x),
            lerp(_camera_y_boundaries.x, _camera_y_boundaries.y, alpha_y)};
}

Vector2f Camera::projectCoordSubscreenToCore(const Vector2f &point) const {
    float alpha_x = (point.x - _subscreen_x_boundaries.x) / getSubscreenWidth();
    float alpha_y = (point.y - _subscreen_y_boundaries.x) / getSubscreenHeight();

    return {lerp(_camera_x_boundaries.x, _camera_x_boundaries.y, alpha_x),
            lerp(_camera_y_boundaries.x, _camera_y_boundaries.y, alpha_y)};
}

Vector2f Camera::projectSizeCoreToGame(const Vector2f &size) const {
    return {std::abs(getSubscreenWidth()) / getWidth() * size.x, std::abs(getSubscreenHeight()) / getHeight() * size.y};
}
