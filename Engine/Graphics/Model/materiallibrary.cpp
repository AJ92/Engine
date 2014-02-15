#include "materiallibrary.h"

MaterialLibrary::MaterialLibrary() :
    EventListener(),
    EventTransmitter()
{
}


void MaterialLibrary::initialize(){
    debugMessage("materiallibrary initializing...");
    //stuff here
    debugMessage("materiallibrary initialized.");
}
