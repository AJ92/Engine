#include "entitymanager.h"
#include "Object/entity.h"

EntityManager::EntityManager() :
    Object()
{
}

void EntityManager::update(float mFT){
    for(auto& e : entities) e->update(mFT);
}

//we only manage we dont actually bother about displaying and stuff... ObjectWorld should do that
/*
void EntityManager::draw(){
    for(auto& e : entities) e->draw();
}
*/

void EntityManager::addToGroup(SP<Entity> mEntity, Group mGroup){
    groupedEntities[mGroup].emplace_back(mEntity);
}

std::vector<SP<Entity> > &EntityManager::getEntitiesByGroup(Group mGroup){
    return groupedEntities[mGroup];
}

void EntityManager::refresh(){
    for(auto i(0u); i < maxGroups; ++i)
    {
        auto& v(groupedEntities[i]);

        v.erase(
            std::remove_if(std::begin(v), std::end(v),
            [i](SP<Entity> mEntity)
            {
                return !mEntity->isAlive() || !mEntity->hasGroup(i);
            }),
            std::end(v)
        );
    }

    entities.erase(
        std::remove_if(std::begin(entities), std::end(entities),
        [](SP<Entity> mEntity)
        {
            return !mEntity->isAlive();
        }),
        std::end(entities)
    );
}

SP<Entity> EntityManager::addEntity(){
    SP<Entity> e(new Entity(*this));
    entities.emplace_back(e);
    return e;
}
