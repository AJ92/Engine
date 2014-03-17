#ifndef EVENTSTREAMER_H
#define EVENTSTREAMER_H

#include "Graphics/Model/model.h"

class EventStreamer
{
public:
    EventStreamer(Model* mdl);
    ~EventStreamer();

    Model * getModel();
    void setModel(Model* mdl);

private:
    Model * mdl;
};

#endif // EVENTSTREAMER_H
