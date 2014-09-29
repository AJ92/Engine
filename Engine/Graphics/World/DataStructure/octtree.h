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
    ~OctTree();

    void constructNodePoints();

    int fits(CompositeObject * obj);
    void subdivide();

    int addModel(CompositeObject * obj);
    int addModels(ModelLibrary_v2 * lib);

    ModelLibrary_v2 * getModelLibrary();

    QList<OctTree* > getNodesInFrustum(Frustum * f);

    QString debug_string();

    enum NodeType {
        NodeRoot                    = 0x0000,
        NodeInner                   = 0x0001,
        NodeLeaf                    = 0x0002
    };

    //The event type.
    NodeType type;

private:
    //the subdivided "sub-cubes"
    OctTree* tree_northwest_high;
    OctTree* tree_northeast_high;
    OctTree* tree_southwest_high;
    OctTree* tree_southeast_high;

    OctTree* tree_northwest_low;
    OctTree* tree_northeast_low;
    OctTree* tree_southwest_low;
    OctTree* tree_southeast_low;

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
    ModelLibrary_v2 * mdllib;
    QHash<unsigned long long, CompositeObject* > id_compositeobject_hash;


    ModelLibrary * real_lib;
    QString path;

    QList<Vector3> node_bounds;



    //event stuff
    void debugMessage(QString message);
    void eventRecieved(Event e);

};

#endif // OCTTREE_H
