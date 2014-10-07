#include "eventstreamer.h"

EventStreamer::EventStreamer(SP<Model> mdl):
    mdl(mdl)
{
}

EventStreamer::~EventStreamer(){

}

SP<Model> EventStreamer::getModel(){
    return mdl;
}

void EventStreamer::setModel(SP<Model> mdl){
    this->mdl = mdl;
}
