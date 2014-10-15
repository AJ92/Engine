/*
 *  An OctTree for storing more or less static objects...
 *  Pre-sorts the meshs by materials so that the renderer
 *  only needs to render them....
 *
 *  Moving and scaling the objects shouldn't be done.. (atm can't be done...)
 *
 *  rotation is supported...
 *
 *    CompositeObjects with MODELS as DATA only (Positation should be provided!!!)
 *
 */

#ifndef OCTTREE_H
#define OCTTREE_H

#include "Event/eventtransmitter.h"
#include "Math/mathematics.h"

#include "Graphics/Model/modellibrary.h"
#include "Graphics/Camera/frustum.h"

#include <QList>
#include <QHash>

#include "Object/SmartPointer/smartpointer.h"

#include "Math/Intersections/intersections.h"

class Event;
class CompositeObject;
class Positation;

class OctTree : virtual public EventListener, virtual public EventTransmitter
{
public:
    //for root node
    OctTree(int max_amount_objects);

    //for inner/leaf nodes
    OctTree(int subdiv_lvl,Vector3 pos, double node_size, int max_amount_objects);
    virtual ~OctTree();

    void constructNodePoints();

    int fits(SP<CompositeObject> obj);
    void subdivide();

    int addModel(SP<CompositeObject> obj);
    int addModels(SP<ModelLibrary_v2> lib);

    SP<ModelLibrary_v2> getModelLibrary();

    QList<SP<OctTree> > getNodesInFrustum(SP<Frustum> f);

    QString debug_string();

    enum NodeType {
        NodeRoot                    = 0x0000,
        NodeInner                   = 0x0001,
        NodeLeaf                    = 0x0002
    };

    //The event type.
    NodeType type;

    Vector3 getPosition();
    double getSize();

private:

    SP<OctTree> me;
    SP<EventListener> me_eventListener;

    //the subdivided "sub-cubes"
    SP<OctTree> tree_northwest_high;
    SP<OctTree> tree_northeast_high;
    SP<OctTree> tree_southwest_high;
    SP<OctTree> tree_southeast_high;

    SP<OctTree> tree_northwest_low;
    SP<OctTree> tree_northeast_low;
    SP<OctTree> tree_southwest_low;
    SP<OctTree> tree_southeast_low;

    //info about the current node
    int subdivision_level;
    bool is_subdivided;

    //node size and location in 3D space
    Vector3 pos;
    double node_size;
    double spherical_node_size;

    //treshold for subdivision
    int max_amount_objects;
    int amount_objects;

    //internal data
    SP<ModelLibrary_v2> mdllib;
    QHash<unsigned long long, SP<CompositeObject> > id_compositeobject_hash;


    SP<ModelLibrary> real_lib;
    QString path;

    QList<Vector3> node_bounds;
    AABB aabb;
    Sphere sphere;


    //event stuff
    void debugMessage(QString message);
    void eventRecieved(Event e);

};

#endif // OCTTREE_H
