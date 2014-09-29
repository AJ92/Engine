#ifndef MODELLOADER_H
#define MODELLOADER_H

#include "Graphics/Model/Streamer/streamer.h"
#include "Graphics/Model/model.h"
#include "Threading/threadaccountant.h"

class Event;

class ModelLoader : virtual public EventListener, virtual public EventTransmitter
{
public:
    ModelLoader(ThreadAccountant * ta);
    void initialize();

    void loadModel(Model *m);
    QList<Model*> getModels() const;

    // should be unsigned long long or so
    int modelCount();
    void setModelsPerThread(int model_count);

    void debugModelData();


private:
    ThreadAccountant * ta;
    Streamer * streamer;    

    //model lists
    QList<Model*> all_models_list;                  //all models (includes instances)
    QList<Model*> unique_models_list;               //unique by data!!!
    QList<QString> unique_model_paths_list;         //unique paths of models


    QList<QList<Model*> > instances_to_load_list;   //instances which need to be loaded,
                                                    //because the base model wans't loaded
                                                    //during the instance process...

    void eventRecieved(Event e);
    void debugMessage(QString message);

    void addModel(Model * mdl);
    void addModelUnique(Model * mdl);
    void addModelInstanceToLoad(Model * mdl);

    void updateInstances(Model * mdl);

    Model * containsModelData(Model * mdl);
    Model * containsModel(Model * mdl);
    bool removeModel(Model * mdl);
};

#endif // MODELLOADER_H
