#include "eventmodel.h"

#include "Graphics/Model/model.h"

EventModel::EventModel(SP<Model> mdl)
{
    this->mdl = mdl;
}

EventModel::~EventModel(){

}

SP<Model> EventModel::getModel(){
    return mdl;
}

void EventModel::setModel(SP<Model> mdl){
    this->mdl = mdl;
}
