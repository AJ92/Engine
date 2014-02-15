#ifndef MATERIALLIBRARY_H
#define MATERIALLIBRARY_H

#include "Object/object.h"
#include "Event/eventtransmitter.h".h"
#include <QString>
#include <list>
#include "Graphics/Model/model.h"


class MaterialLibrary : virtual public EventListener, virtual public EventTransmitter
{
public:
    MaterialLibrary();

    void initialize();
};

#endif // MATERIALLIBRARY_H
