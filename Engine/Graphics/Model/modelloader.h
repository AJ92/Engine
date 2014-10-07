#ifndef MODELLOADER_H
#define MODELLOADER_H

#include "Graphics/Model/Streamer/streamer.h"
#include "Graphics/Model/model.h"
#include "Threading/threadaccountant.h"

#include "Object/SmartPointer/smartpointer.h"

class Event;

class ModelLoader : virtual public EventListener, virtual public EventTransmitter
{
public:
    ModelLoader(SP<ThreadAccountant> ta);
    void initialize();

    void loadModel(SP<Model> m);
    QList<SP<Model> > getModels() const;

    // should be unsigned long long or so
    int modelCount();
    void setModelsPerThread(int model_count);

    void debugModelData();


private:
    SP<ThreadAccountant> ta;
    SP<Streamer> streamer;

    //model lists
    QList<SP<Model> > all_models_list;                  //all models (includes instances)
    QList<SP<Model> > unique_models_list;               //unique by data!!!


    QList<QString> unique_model_paths_list;         //unique paths of models
    QList<QList<SP<Model> > > instances_to_load_list;   //instances which need to be loaded,
                                                    //because the base model wans't loaded
                                                    //during the instance process...

    void eventRecieved(Event e);
    void debugMessage(QString message);

    void addModel(SP<Model> mdl);
    void addModelUnique(SP<Model> mdl);
    void addModelInstanceToLoad(SP<Model> mdl);

    void updateInstances(SP<Model> mdl);

    SP<Model> containsModelData(SP<Model> mdl);
    SP<Model> containsModel(SP<Model> mdl);
    bool removeModel(SP<Model> mdl);
};

#endif // MODELLOADER_H
