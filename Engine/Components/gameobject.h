#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Object/object.h"
#include <QString>
#include "Graphics/Renderer/renderer.h"

class GraphicsComponent;
class LocationComponent;

class GameObject : public Object
{
public:

    //extend to 32 bit if needed... ( 0xFFFFFFFF)
    enum GameObjectType {
  
        ObjectEmpty             = 0x0000,

        ObjectLocationComponent = 0x0001,

        ObjectGraphicsComponent = 0x0002,
        ObjectPhysicsComponent  = 0x0004,
        ObjectInputComponent    = 0x0008,

        ObjectCamera            = 0x0010,

        ObjectError             = 0xFFFF
        //more to follow...
    };

    GameObject();
    GameObject(QString name);

    void addGraphicsComponent(GraphicsComponent * component);
    bool hasGraphicsComponent();
    GraphicsComponent* getGraphicsComponent();

    void addLocationComponent(LocationComponent * component);
    bool hasLocationComponent();
    LocationComponent* getLocationComponent();

    //will receive some more stuuf like
    // - world for physics
    // - renderer for graphics
    // ...
    void update(Renderer &renderer);


    QString getName();
    void setName(QString name);

    QString toString();

    int getType();

private:
    QString name_;
    int type_;

    //all the Objects this component can have...
    GraphicsComponent * graphicscomponent_;
    LocationComponent * locationcomponent_;
};

#endif // GAMEOBJECT_H
