#include "EntityView.h"

EntityView::EntityView(std::weak_ptr<Entity> entity) : _entity(std::move(entity)) {

}

sf::VertexArray EntityView::getHitbox() const {
    sf::VertexArray hitbox_draw = sf::VertexArray(sf::LineStrip, 5);

    std::shared_ptr<Entity> shared_entity = _entity.lock();
    if (shared_entity) {
        std::shared_ptr<Hitbox> hitbox = shared_entity->getScreenHitbox();
        if (!hitbox) return sf::VertexArray(sf::LineStrip, 0);

        Vector2f half_size = hitbox->getSize() / 2;
        Vector2f origin_point = hitbox->getPosition();

        hitbox_draw[0].position = sf::Vector2f(origin_point.x - half_size.x, origin_point.y - half_size.y);
        hitbox_draw[1].position = sf::Vector2f(origin_point.x + half_size.x, origin_point.y - half_size.y);
        hitbox_draw[2].position = sf::Vector2f(origin_point.x + half_size.x, origin_point.y + half_size.y);
        hitbox_draw[3].position = sf::Vector2f(origin_point.x - half_size.x, origin_point.y + half_size.y);
        hitbox_draw[4] = hitbox_draw[0];

        for (int i = 0; i < 5; i++) {
            hitbox_draw[i].color = sf::Color::Magenta;
        }
    }

    return hitbox_draw;
}

sf::VertexArray EntityView::getRays() const {
    sf::VertexArray rays_draw = sf::VertexArray(sf::Lines, 0);

    std::shared_ptr<Entity> shared_entity = _entity.lock();
    if (shared_entity) {
        std::vector<std::shared_ptr<Ray>> rays = shared_entity->getScreenRays();

        rays_draw = sf::VertexArray(sf::Lines, rays.size() * 2);

        for (int i = 0; i < rays.size(); i++) {
            rays_draw[i * 2].position = sf::Vector2f({rays[i]->getOriginPoint().x, rays[i]->getOriginPoint().y});
            rays_draw[i * 2 + 1].position = sf::Vector2f({rays[i]->getEndPoint().x, rays[i]->getEndPoint().y});

            rays_draw[i * 2].color = sf::Color::Yellow;
            rays_draw[i * 2 + 1].color = sf::Color::Yellow;
        }
    }

    return rays_draw;
}
