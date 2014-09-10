#ifndef EVENTMODEL_H
#define EVENTMODEL_H


class Model;

class EventModel
{
public:   
    EventModel(Model * mdl);
    ~EventModel();

    Model * getModel();
    void setModel(Model * mdl);

private:
    Model * mdl;
};

#endif // EVENTMODEL_H