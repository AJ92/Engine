#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QString>
#include "Components/Interfaces/graphicscomponent.h"

class GraphicsComponent;

class GameObject
{
public:

    enum GameObjectType {
        //single object types (Elementary Types)
        ObjectEmpty             = 0x0000,

        ObjectCamera            = 0x0001,

        //multiple object types (Composite Types)
        ObjectGraphicsComponent = 0x0002,
        ObjectPhysicsComponent  = 0x0004,
        ObjectInputComponent    = 0x0008,

        ObjectError             = 0x0100
        //more to follow...
    };

    GameObject();
    GameObject(QString name);


    //multiple object components
    void addGraphicsComponent(GraphicsComponent * graphicscomponent);
    GraphicsComponent* getGraphicsComponent();


    void update();


    QString getName();
    void setName(QString name);

    QString toString();

    int getType();

private:
    QString name_;
    int type_;

    //all the Objects this component can have...
    GraphicsComponent * graphicscomponent_;
};

#endif // GAMEOBJECT_H
