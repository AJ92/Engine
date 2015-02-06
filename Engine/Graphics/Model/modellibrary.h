#ifndef MODELLIBRAY_H
#define MODELLIBRAY_H

#include "Object/object.h"
#include <QString>
#include <QList>

#include "Graphics/Model/Streamer/streamer.h"

#include "Threading/threadaccountant.h"
#include "Object/SmartPointer/smartpointer.h"

class Model;
class Mesh;
class Material;
class Event;
class CompositeObject;

class ModelLibrary : virtual public EventListener, virtual public EventTransmitter
{
public:
    ModelLibrary(SP<ThreadAccountant> ta);
    virtual ~ModelLibrary();

    void initialize();

    SP<Model> loadModel(QString path);
    QList<SP<Model> > getModels() const;

    // should be unsigned long long or so
    int modelCount();
    void setModelsPerThread(int model_count);

    //getter for the renderer... should be manipulated
    QList<QList<SP<Mesh> > > getMeshModelList();
    QList<QList<SP<Model> > > getModelMeshList();
    QList<SP<Material> > getMaterialMeshList();

    void debugModelData();


private:
    SP<ThreadAccountant> ta;
    SP<Streamer> streamer;
    //models


    //model lists
    QList<SP<Model> > model_list;               //all models (includes instances)
    QList<SP<Model> > unique_model_list;        //unique by data!!!
    QList<QString> unique_model_path_list;  //unique paths of models
    QList<QList<SP<Model> > > instances_to_load_list;   //instances which need to be loaded,
                                                    //because the base model wans't loaded
                                                    //during the instance process...

    //model data sorted by material / single mesh
    QList<QList<SP<Mesh> > > mesh_model_list;
    QList<QList<SP<Model> > > model_mesh_list;
    QList<SP<Material> > material_mesh_list;

    void eventRecieved(Event e);
    void debugMessage(QString message);

    void addModel(SP<Model> mdl);
    void addModelUnique(SP<Model> mdl);
    void addModelInstanceToLoad(SP<Model> mdl);

    void addModelData(SP<Model> mdl);

    void updateInstances(SP<Model> mdl);

    SP<Model> containsModelData(SP<Model> mdl);
    SP<Model> containsModel(SP<Model> mdl);
    bool removeModel(SP<Model> mdl);
};



class ModelLibrary_v2 : virtual public EventListener, virtual public EventTransmitter
{
public:
    ModelLibrary_v2();
    ModelLibrary_v2(int reserve_unique, int reserve_all);

    virtual ~ModelLibrary_v2();

    void initialize();

    void addModel(SP<CompositeObject> co);
    bool removeModel(SP<CompositeObject> co);

    void clearLib();

    QList<SP<Model> > getModels() const;

    QList<SP<CompositeObject> > getCompositeObjects() const;


    // should be unsigned long long or so
    int modelCount();


    //getter for the renderer... shouldn't be manipulated

    QList<QList<SP<CompositeObject> > > getCompositeobjectMeshList();

    QList<QList<SP<Mesh> > > getMeshModelList();
    QList<QList<SP<Model> > > getModelMeshList();
    QList<SP<Material> > getMaterialMeshList();

    void debugModelData();


private:

    QList<SP<Model> > model_list;               //all models (includes instances)
    QList<SP<CompositeObject> > compositeobject_list;        //all compositeobjects


    //model data sorted by material / single mesh

    QList<QList<SP<CompositeObject> > > compositeobject_mesh_list;
    QList<QList<SP<Mesh> > > mesh_model_list;
    QList<QList<SP<Model> > > model_mesh_list;
    QList<SP<Material> > material_mesh_list;

    void eventRecieved(Event e);
    void debugMessage(QString message);


    void addModelData(SP<CompositeObject> co);

    //next 2 not needed ?
    SP<Model> containsModelData(SP<Model> mdl);
    SP<Model> containsModel(SP<Model> mdl);

    SP<CompositeObject> containsCompositeObject(SP<CompositeObject> co);

    int reserve_unique;
    int reserve_all;

};


#endif // MODELLIBRAY_H
