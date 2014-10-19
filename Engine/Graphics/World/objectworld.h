#ifndef OBJECTWORLD_H
#define OBJECTWORLD_H

#include "Object/object.h"

#include "Event/eventtransmitter.h"
#include "mathematics.h"

#include "Threading/threadaccountant.h"

#include "Graphics/Model/modelloader.h"

#include "Graphics/World/DataStructure/octtree.h"
#include "Graphics/World/DataStructure/octtreefast.h"

#include <QList>

#include "Object/SmartPointer/smartpointer.h"

class Event;
class CompositeObject;
class Positation;

class ObjectWorld : virtual public EventListener, virtual public EventTransmitter
{
public:
    ObjectWorld(SP<ThreadAccountant> ta);
    ~ObjectWorld();

    void setModelLoader(SP<ModelLoader> ml);
    void setModelsPerThread(int model_count);
    void setLightModelPath(QString path);
    void setUnitCubeModelPath(QString path);

    SP<Model> getUnitCubeModel();

    void initialize();

    SP<OctTree> getOctTree();
    SP<OctTreeFast> getOctTreeFastDynamicModels();
    SP<OctTreeFast> getOctTreeFastDynamicLights();

    //creates an empty CompositeObject with Positation so the user can already interact
    //even if the model isn't loaded yet... model is bound later to this object...
    SP<CompositeObject> loadLightobject(QString name);
    SP<CompositeObject> loadModelobject(QString name, QString path);
    SP<CompositeObject> loadModelobject(QString name, QString path, SP<Positation> posi);

private:

    SP<EventListener> me_eventListener;

    SP<ThreadAccountant> ta;
    SP<ModelLoader> ml;

    QString light_model_path;
    SP<Model> light_model;

    QString unitcube_model_path;
    SP<Model> unitcube_model;

    SP<OctTree> ot;

    SP<OctTreeFast> ot_dynamic_model;
    SP<OctTreeFast> ot_dynamic_lights;

    //private functions...
    void loadModel(SP<Model> m);


    //EventListener and EventTransmitter...
    void eventRecieved(Event e);
    void debugMessage(QString message);

    int count_models_in;
    int count_models_out;




    //temporary store all Composite objects so we dont delete them accidently...
    QList<SP<CompositeObject> > all_comp_objs;
};

#endif // OBJECTWORLD_H
