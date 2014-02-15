#ifndef MODELLIBRAY_H
#define MODELLIBRAY_H

#include "Object/object.h"
#include <QString>
#include <list>

#include "Graphics/Model/Streamer/streamer.h"
#include "Graphics/Model/model.h"

#include "Threading/threadaccountant.h"

class ModelLibrary : virtual public EventListener, virtual public EventTransmitter
{
public:
    ModelLibrary(ThreadAccountant * ta);

    void initialize();

    Model* loadModel(QString path);
    std::list<Model*> getModels() const;

    // should be unsigned long long or so
    int modelCount();
    void setModelsPerThread(int model_count);


private:
    ThreadAccountant * ta;
    Streamer * streamer;
    std::list<Model*> model_list;
    std::list<Model*> unique_model_list; //unique by data!!!

    void debugMessage(QString message);

    void addModel(Model * mdl);
    Model * containsModelData(Model * mdl);
    Model * containsModel(Model * mdl);
    bool removeModel(Model * mdl);
};

#endif // MODELLIBRAY_H
