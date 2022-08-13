#ifndef GAMEENGINE_IENTITYVIEWCREATOR_H
#define GAMEENGINE_IENTITYVIEWCREATOR_H


#include <memory>
#include <vector>
#include <map>
#include "Entity.h"
#include "../animation/AnimationData.h"

class IEntityViewCreator {
public:
    virtual void loadTextureGroup(const std::string &texture_resource_name,
                                  const std::vector<std::string> &texture_filenames) = 0;

    virtual void createEntitySpriteView(std::shared_ptr<Entity> entity, const std::string &texture_group_name,
                                        unsigned int layer) = 0;

    virtual void createEntityTextView(std::shared_ptr<Entity> entity) = 0;
};


#endif //GAMEENGINE_IENTITYVIEWCREATOR_H
