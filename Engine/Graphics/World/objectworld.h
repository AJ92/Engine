#ifndef OBJECTWORLD_H
#define OBJECTWORLD_H

#include "Object/object.h"

#include "Event/eventtransmitter.h"
#include "Math/mathematics.h"

#include "Threading/threadaccountant.h"

#include "Graphics/Model/modelloader.h"

#include "Graphics/World/DataStructure/octtree.h"

#include <QList>

class Event;
class CompositeObject;
class Positation;

class ObjectWorld : virtual public EventListener, virtual public EventTransmitter
{
public:
    ObjectWorld(ThreadAccountant * ta);
    ~ObjectWorld();

    void setModelLoader(ModelLoader * ml);
    void setModelsPerThread(int model_count);

    void initialize();

    OctTree * getOctTree();

    //creates an empty CompositeObject with Positation so the user can already interact
    //even if the model isn't loaded yet... model is bound later to this object...
    CompositeObject * loadModelobject(QString name, QString path);

private:
    ThreadAccountant * ta;
    ModelLoader * ml;

    OctTree * ot;

    //private functions...
    Model* loadModel(QString path);


    //EventListener and EventTransmitter...
    void eventRecieved(Event e);
    void debugMessage(QString message);
};

#endif // OBJECTWORLD_H
