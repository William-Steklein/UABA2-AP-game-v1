#include "HPBar.h"

HPBar::HPBar(const Vector2f &position, std::shared_ptr<Camera> camera, const Vector2f &viewSize,
             AnimationPlayer animationPlayer, AudioPlayer audioPlayer, bool staticView)
        : UIEntity(position, std::move(camera), viewSize, std::move(animationPlayer), std::move(audioPlayer),
                   staticView), _nr_hp_max(0), _nr_hp_current(0) {

}

void HPBar::setHearts(std::weak_ptr<PhysicsEntity> entity, const std::weak_ptr<HPBar> &hp_bar_ptr, bool left_alligned,
                      const Vector2f &heart_size, const Vector2f &offset) {
    _affected_entity = std::move(entity);

    if (!_affected_entity.expired()) {
        std::shared_ptr<PhysicsEntity> affected_entity = _affected_entity.lock();
        _nr_hp_max = affected_entity->getMaxHitPoints();
        _view_size = heart_size;

        float x_spacing = _view_size.x + _view_size.x * constants::hpbarhearts::horizontal_distance_multiplier;
        float current_x_pos;
        if (left_alligned) {
            current_x_pos = 0;
        } else {
            current_x_pos = -(static_cast<float>(_nr_hp_max - 1) * x_spacing) / 2;
        }

        for (unsigned int i = 0; i < _nr_hp_max; i++) {
            Vector2f heart_position = Vector2f(current_x_pos, 0) + offset;
            _hearts.push_back(std::make_shared<Heart>(
                    Heart(heart_position, _camera, _view_size, _animation_player)));
            current_x_pos += x_spacing;
            addChild(_hearts.back(), hp_bar_ptr);
        }

        // update if hp not max
        if (_nr_hp_max != affected_entity->getCurrentHitPoints()) {
            updateHearts(affected_entity->getCurrentHitPoints());
        }
    }
}

std::vector<std::shared_ptr<Heart>> HPBar::getHearts() {
    return _hearts;
}

void HPBar::update(double t, float dt) {
    if (!_affected_entity.expired()) {
        std::shared_ptr<PhysicsEntity> affected_entity = _affected_entity.lock();

        if (_nr_hp_current != affected_entity->getCurrentHitPoints()) {
            updateHearts(affected_entity->getCurrentHitPoints());
        }
    }

    UIEntity::update(t, dt);
}

void HPBar::updateHearts(unsigned int current_hp) {
    _nr_hp_current = current_hp;

    unsigned int hp_counter = 0;

    for (const auto &heart: _hearts) {
        if (hp_counter < _nr_hp_current) {
            heart->setFull(true);
        } else {
            heart->setFull(false);
        }

        hp_counter++;
    }
}