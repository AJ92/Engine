#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "Object/object.h"
#include "Object/entity.h"
#include "Object/CompositionHelper.h"

#include <vector>
#include <bitset>
#include <memory>
#include <array>

class Entity;

class EntityManager : public Object
{
public:
    EntityManager();

    void update(float mFT);
    //void draw();

    void addToGroup(Entity* mEntity, Group mGroup);

    std::vector<Entity*>& getEntitiesByGroup(Group mGroup);

    void refresh();

    Entity& addEntity();

private:
    std::vector<std::unique_ptr<Entity>> entities;
    std::array<std::vector<Entity*>, maxGroups> groupedEntities;
};

#endif // ENTITYMANAGER_H
