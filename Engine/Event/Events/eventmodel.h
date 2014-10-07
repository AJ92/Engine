#ifndef EVENTMODEL_H
#define EVENTMODEL_H

#include "Object/SmartPointer/smartpointer.h"

class Model;

class EventModel
{
public:   
    EventModel(SP<Model> mdl);
    ~EventModel();

    SP<Model> getModel();
    void setModel(SP<Model> mdl);

private:
    SP<Model> mdl;
};

#endif // EVENTMODEL_H
