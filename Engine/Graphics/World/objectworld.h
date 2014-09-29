#ifndef OBJECTWORLD_H
#define OBJECTWORLD_H

#include "Object/object.h"

#include "Event/eventtransmitter.h"
#include "Math/mathematics.h"

#include "Threading/threadaccountant.h"

#include "Graphics/Model/modelloader.h"

#include "Graphics/World/DataStructure/octtree.h"
#include "Graphics/World/DataStructure/octtreefast.h"

#include <QList>

class Event;
class CompositeObject;
class Positation;

class ObjectWorld : virtual public EventListener, virtual public EventTransmitter
{
public:
    ObjectWorld(ThreadAccountant * ta);
    ~ObjectWorld();

    void setModelLoader(ModelLoader * ml);
    void setModelsPerThread(int model_count);
    void setLightModelPath(QString path);

    void initialize();

    OctTree * getOctTree();
    OctTreeFast * getOctTreeFastDynamicModels();
    OctTreeFast * getOctTreeFastDynamicLights();

    //creates an empty CompositeObject with Positation so the user can already interact
    //even if the model isn't loaded yet... model is bound later to this object...
    CompositeObject * loadLightobject(QString name);
    CompositeObject * loadModelobject(QString name, QString path);
    CompositeObject * loadModelobject(QString name, QString path, Positation * posi);

private:
    ThreadAccountant * ta;
    ModelLoader * ml;

    QString light_model_path;
    Model * light_model;

    OctTree * ot;

    OctTreeFast * ot_dynamic_model;
    OctTreeFast * ot_dynamic_lights;

    //private functions...
    void loadModel(Model *m);

    void addModelToOctTree(CompositeObject * co);


    //EventListener and EventTransmitter...
    void eventRecieved(Event e);
    void debugMessage(QString message);

    int count_models_in;
    int count_models_out;
};

#endif // OBJECTWORLD_H
