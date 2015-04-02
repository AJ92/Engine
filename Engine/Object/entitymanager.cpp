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

void EntityManager::addToGroup(Entity* mEntity, Group mGroup){
    groupedEntities[mGroup].emplace_back(mEntity);
}

std::vector<Entity*>& EntityManager::getEntitiesByGroup(Group mGroup){
    return groupedEntities[mGroup];
}

void EntityManager::refresh(){
    for(auto i(0u); i < maxGroups; ++i)
    {
        auto& v(groupedEntities[i]);

        v.erase(
            std::remove_if(std::begin(v), std::end(v),
            [i](Entity* mEntity)
            {
                return !mEntity->isAlive() || !mEntity->hasGroup(i);
            }),
            std::end(v)
        );
    }

    entities.erase(
        std::remove_if(std::begin(entities), std::end(entities),
        [](const std::unique_ptr<Entity>& mEntity)
        {
            return !mEntity->isAlive();
        }),
        std::end(entities)
    );
}

Entity& EntityManager::addEntity(){
    Entity* e(new Entity(*this));
    std::unique_ptr<Entity> uPtr{e};
    entities.emplace_back(std::move(uPtr));
    return *e;
}
