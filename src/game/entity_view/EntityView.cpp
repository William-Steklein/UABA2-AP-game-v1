#include "EntityView.h"

EntityView::EntityView(std::weak_ptr<Entity> entity) : _entity(std::move(entity)) {

}
