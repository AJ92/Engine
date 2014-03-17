#include "eventstreamer.h"

EventStreamer::EventStreamer(Model * mdl):
    mdl(mdl)
{
}

EventStreamer::~EventStreamer(){

}

Model * EventStreamer::getModel(){
    return mdl;
}

void EventStreamer::setModel(Model* mdl){
    this->mdl = mdl;
}
