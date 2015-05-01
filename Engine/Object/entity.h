#ifndef ENTITY_H
#define ENTITY_H

#include "Object/object.h"
#include "Object/component.h"
#include "Object/entitymanager.h"

#include <vector>
#include <bitset>
#include <memory>

#include "Object/SmartPointer/smartpointer.h"



class EntityManager;


class Entity : public Component
{

public:

    enum EntityGroup : std::size_t
    {
        InternalSystem,
        Graphics,
        Phyisics,
        Logic
    };

    Entity(EntityManager& mManager);

    void update(float mFT);
    //void draw();

    bool isAlive() const;
    void destroy();


    bool hasGroup(Group mGroup) const noexcept;

    void addGroup(Group mGroup) noexcept;
    void delGroup(Group mGroup) noexcept;

    template<typename T> bool hasComponent() const{
        return componentBitset[getComponentTypeID<T>()];
    }

    //argument forwarding...
    template<typename T, typename... TArgs> SP<T> addComponent(TArgs&&... mArgs){
        assert(!hasComponent<T>());

        SP<T> c(new T(std::forward<TArgs>(mArgs)...));
        c->setParent(this);

        //template keyword is needed, other wise symbols '<' and '>' might get interpreted
        //as less and greater ...
        //casting the pointer in our smartpointer , but keeping the same refcounter
        SP<Component> s_ptr_c = c.template castTo<Component>();

        components.emplace_back(std::move(s_ptr_c));
        componentArray[getComponentTypeID<T>()] = s_ptr_c;
        componentBitset[getComponentTypeID<T>()] = true;

        c->init();
        return c;
    }



    template<typename T> SP<T> getComponent() const{
        assert(hasComponent<T>());
        //auto ptr(componentArray[getComponentTypeID<T>()]);
        //return *reinterpret_cast<T*>(ptr);
        SP<Component> s_ptr(componentArray[getComponentTypeID<T>()]);
        //template keyword is needed, other wise symbols '<' and '>' might get interpreted
        //as less and greater ...
        //reinterpret casting the pointer in our smartpointer , but keeping the same refcounter
        ///////reinterpretcast is EVIL !!!
        //return s_ptr.template reinterpretCastTo<T>();
        return s_ptr.template dynamicCastTo<T>();
    }



private:
    EntityManager& manager;

    bool alive{true};
    std::vector<SP<Component> > components;
    ComponentArray componentArray;
    ComponentBitset componentBitset;

    GroupBitset groupBitset;
};

#endif // ENTITY_H
