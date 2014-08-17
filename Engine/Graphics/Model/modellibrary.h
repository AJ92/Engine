#ifndef MODELLIBRAY_H
#define MODELLIBRAY_H

#include "Object/object.h"
#include <QString>
#include <QList>

#include "Graphics/Model/Streamer/streamer.h"
#include "Graphics/Model/model.h"

#include "Threading/threadaccountant.h"

class ModelLibrary : virtual public EventListener, virtual public EventTransmitter
{
public:
    ModelLibrary(ThreadAccountant * ta);

    void initialize();

    Model* loadModel(QString path);
    QList<Model*> getModels() const;

    // should be unsigned long long or so
    int modelCount();
    void setModelsPerThread(int model_count);

    //getter for the renderer... should be manipulated
    QList<QList<Mesh*> > getMeshModelList();
    QList<QList<Model*> > getModelMeshList();
    QList<Material*> getMaterialMeshList();

    void debugModelData();


private:
    ThreadAccountant * ta;
    Streamer * streamer;
    //models


    //model lists
    QList<Model*> model_list;               //all models (includes instances)
    QList<Model*> unique_model_list;        //unique by data!!!
    QList<QString> unique_model_path_list;  //unique paths of models
    QList<QList<Model*> > instances_to_load_list;   //instances which need to be loaded,
                                                    //because the base model wans't loaded
                                                    //during the instance process...

    //model data sorted by material / single mesh
    QList<QList<Mesh*> > mesh_model_list;
    QList<QList<Model*> > model_mesh_list;
    QList<Material*> material_mesh_list;

    void eventRecieved(Event e);
    void debugMessage(QString message);

    void addModel(Model * mdl);
    void addModelUnique(Model * mdl);
    void addModelInstanceToLoad(Model * mdl);

    void addModelData(Model * mdl);

    void updateInstances(Model * mdl);

    Model * containsModelData(Model * mdl);
    Model * containsModel(Model * mdl);
    bool removeModel(Model * mdl);
};



class ModelLibrary_v2 : virtual public EventListener, virtual public EventTransmitter
{
public:
    ModelLibrary_v2();

    void initialize();

    void addModel(Model * mdl);

    // should be unsigned long long or so
    int modelCount();


    //getter for the renderer... shouldn't be manipulated
    QList<QList<Mesh*> > getMeshModelList();
    QList<QList<Model*> > getModelMeshList();
    QList<Material*> getMaterialMeshList();

    void debugModelData();


private:

    QList<Model*> model_list;               //all models (includes instances)
    QList<Model*> unique_model_list;        //unique by data!!!
    QList<QString> unique_model_path_list;  //unique paths of models

    //model data sorted by material / single mesh
    QList<QList<Mesh*> > mesh_model_list;
    QList<QList<Model*> > model_mesh_list;
    QList<Material*> material_mesh_list;

    void eventRecieved(Event e);
    void debugMessage(QString message);

    void addModelUnique(Model * mdl);

    void addModelData(Model * mdl);

    Model * containsModelData(Model * mdl);
    Model * containsModel(Model * mdl);
    bool removeModel(Model * mdl);
};


#endif // MODELLIBRAY_H
