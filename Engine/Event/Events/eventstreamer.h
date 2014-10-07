#ifndef EVENTSTREAMER_H
#define EVENTSTREAMER_H

#include "Graphics/Model/model.h"

#include "Object/SmartPointer/smartpointer.h"

class EventStreamer
{
public:
    EventStreamer(SP<Model> mdl);
    ~EventStreamer();

    SP<Model> getModel();
    void setModel(SP<Model> mdl);

private:
    SP<Model> mdl;
};

#endif // EVENTSTREAMER_H
