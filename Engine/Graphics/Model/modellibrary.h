#ifndef MODELLIBRAY_H
#define MODELLIBRAY_H

#include "Object/object.h"
#include <QString>
#include <list>

#include "Graphics/Model/Streamer/streamer.h"
#include "Graphics/Model/model.h"

class ModelLibrary : virtual public EventListener, virtual public EventTransmitter
{
public:
    ModelLibrary();
    ModelLibrary(int maxThreads, int reserved_space);

    void initialize();

    Model* loadModel(QString path);
    std::list<Model*> getModels() const;

    // should be unsigned long long or so
    int modelCount();


private:
    Streamer * streamer;
    std::list<Model*> model_list;

    void debugMessage(QString message);

    void addModel(Model * mdl);
    bool containsModel(Model * mdl) const;
    bool removeModel(Model * mdl);
};

#endif // MODELLIBRAY_H
