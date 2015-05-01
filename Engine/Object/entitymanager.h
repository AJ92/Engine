#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "Object/object.h"
#include "Object/CompositionHelper.h"
//#include "Object/entity.h"
#include "Object/SmartPointer/smartpointer.h"

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

    void addToGroup(SP<Entity> mEntity, Group mGroup);

    std::vector<SP<Entity>>& getEntitiesByGroup(Group mGroup);

    void refresh();

    SP<Entity> addEntity();

private:
    std::vector<SP<Entity>> entities;
    std::array<std::vector<SP<Entity>>, maxGroups> groupedEntities;
};

#endif // ENTITYMANAGER_H
