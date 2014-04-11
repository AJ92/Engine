#ifndef LIGHTLIBRARY_H
#define LIGHTLIBRARY_H

#include "Object/object.h"
#include <QString>
#include <QList>

#include "Graphics/Model/Streamer/streamer.h"
#include "Graphics/Model/model.h"
#include "Graphics/Model/light.h"

#include "Threading/threadaccountant.h"

class LightLibrary : virtual public EventListener, virtual public EventTransmitter
{
public:
    LightLibrary(ThreadAccountant * ta);

    void initialize();

    Light* loadLight(QString path);
    QList<Light*> getLights() const;

    // should be unsigned long long or so
    int lightCount();
    void setLightsPerThread(int light_count);

    //getter for the renderer... should be manipulated
    QList<QList<Mesh*> > getMeshModelList();
    QList<QList<Model*> > getModelMeshList();
    QList<QList<Light*> > getLightMeshList();
    QList<Material*> getMaterialMeshList();

    void debugLightModelData();


private:
    ThreadAccountant * ta;
    Streamer * streamer;
    //lights


    //light lists
    QList<Light*> light_list;               //all lights (includes instances)
    QList<Light*> unique_light_list;        //unique by data!!!
    QList<QString> unique_light_path_list;  //unique paths of models
    QList<QList<Light*> > instances_to_load_list;   //instances which need to be loaded,
                                                    //because the base model wasn't loaded
                                                    //during the instance process...


    //temp lists to bring loaded lights and models back together
    QList<Light*> light_loading;
    QList<Model*> model_loading;


    //light data sorted by material / single mesh
    QList<QList<Mesh*> > mesh_model_list;
    QList<QList<Model*> > model_mesh_list;
    QList<QList<Light*> > light_mesh_list;
    QList<Material*> material_mesh_list;

    void eventRecieved(Event e);
    void debugMessage(QString message);

    void addLight(Light * light);
    void addLightUnique(Light * light);
    void addLightInstanceToLoad(Light * light);

    void addLightData(Light * light);

    void updateInstances(Model * mdl);

    Light * containsLightData(Light * light);
    Light * containsLight(Light * light);
    bool removeLight(Light * light);
};

#endif // LIGHTLIBRARY_H
