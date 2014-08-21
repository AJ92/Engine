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

class ObjectWorld : virtual public EventListener, virtual public EventTransmitter
{
public:
    ObjectWorld(ThreadAccountant * ta);
    ~ObjectWorld();

    void setModelLoader(ModelLoader * ml);
    void setModelsPerThread(int model_count);

    void initialize();

    Model* loadModel(QString path);

private:
    ThreadAccountant * ta;
    ModelLoader * ml;

    OctTree * ot;

    //EventListener and EventTransmitter...
    void eventRecieved(Event e);
    void debugMessage(QString message);
};

#endif // OBJECTWORLD_H
