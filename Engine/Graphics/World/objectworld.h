#ifndef OBJECTWORLD_H
#define OBJECTWORLD_H

#include "Object/object.h"
#include "Event/eventtransmitter.h"
#include "Math/mathematics.h"

#include "Threading/threadaccountant.h"

#include <QList>

class ObjectWorld : virtual public EventListener, virtual public EventTransmitter
{
public:
    ObjectWorld(ThreadAccountant * ta);
    ~ObjectWorld();

    void setModelLoader();

    void initialize();


private:
    ThreadAccountant * ta;

    //EventListener and EventTransmitter...
    void eventRecieved(Event e);
    void debugMessage(QString message);
};

#endif // OBJECTWORLD_H
