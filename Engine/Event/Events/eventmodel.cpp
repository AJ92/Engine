#include "eventmodel.h"

#include "Graphics/Model/model.h"

EventModel::EventModel(Model * mdl)
{
    this->mdl = mdl;
}

EventModel::~EventModel(){

}

Model * EventModel::getModel(){
    return mdl;
}

void EventModel::setModel(Model * mdl){
    this->mdl = mdl;
}
