#ifndef ENTITY_H
#define ENTITY_H

#include "Object/object.h"
#include "Object/component.h"
#include "Object/entitymanager.h"

#include <vector>
#include <bitset>
#include <memory>



class EntityManager;
//class Component;

class Entity : public Component
{

public:
    Entity(EntityManager& mManager);

    void update(float mFT);
    //void draw();

    bool isAlive() const;
    void destroy();

    template<typename T> bool hasComponent() const;

    bool hasGroup(Group mGroup) const noexcept;

    void addGroup(Group mGroup) noexcept;
    void delGroup(Group mGroup) noexcept;

    template<typename T, typename... TArgs> T& addComponent(TArgs&&... mArgs);

    template<typename T> T& getComponent() const;


private:
    EntityManager& manager;

    bool alive{true};
    std::vector<std::unique_ptr<Component>> components;
    ComponentArray componentArray;
    ComponentBitset componentBitset;

    GroupBitset groupBitset;
};

#endif // ENTITY_H
