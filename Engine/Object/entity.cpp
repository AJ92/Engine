#include "entity.h"

Entity::Entity(EntityManager& mManager) :
    Component(),
    manager(mManager)
{
}

void Entity::update(float mFT){
    for(auto& c : components){
         c->update(mFT);
    }
}

/*
void Entity::draw(){
    for(auto& c : components){
        c->draw();
    }
}
*/

bool Entity::isAlive() const{
    return alive;
}

void Entity::destroy(){
    alive = false;
}

template<typename T> bool Entity::hasComponent() const{
    return componentBitset[getComponentTypeID<T>()];
}

bool Entity::hasGroup(Group mGroup) const noexcept{
    return groupBitset[mGroup];
}

void Entity::addGroup(Group mGroup) noexcept{
    groupBitset[mGroup] = true;
    manager.addToGroup(this, mGroup);
}

void Entity::delGroup(Group mGroup) noexcept
{
    groupBitset[mGroup] = false;
}

template<typename T, typename... TArgs> T& Entity::addComponent(TArgs&&... mArgs){
    assert(!hasComponent<T>());

    T* c(new T(std::forward<TArgs>(mArgs)...));
    c->entity = this;
    std::unique_ptr<Component> uPtr{c};
    components.emplace_back(std::move(uPtr));

    componentArray[getComponentTypeID<T>()] = c;
    componentBitset[getComponentTypeID<T>()] = true;

    c->init();
    return *c;
}

template<typename T> T& Entity::getComponent() const{
    assert(hasComponent<T>());
    auto ptr(componentArray[getComponentTypeID<T>()]);
    return *reinterpret_cast<T*>(ptr);
}
