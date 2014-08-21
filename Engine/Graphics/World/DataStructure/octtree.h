#ifndef OCTTREE_H
#define OCTTREE_H

#include "Event/eventtransmitter.h"
#include "Math/mathematics.h"

#include "Graphics/Model/modellibrary.h"
#include "Graphics/Camera/frustum.h"

#include <QList>

class Event;

class OctTree : virtual public EventListener, virtual public EventTransmitter
{
public:
    //for root node
    OctTree(int max_amount_objects);

    //for inner/leaf nodes
    OctTree(int subdiv_lvl,Vector3 pos, double node_size, int max_amount_objects);
    ~OctTree();

    void constructNodePoints();

    //might need to provide an entity method aswell...
    int fits(Model * mdl);
    void subdivide();

    int addModel(Model * mdl);
    int addModels(ModelLibrary_v2 * lib);

    QList<OctTree* > getNodesInFrustum(Frustum * f);

    QString debug_string();

    void setDebugMdl(ModelLibrary * real_lib, QString path);
    Model * getDebugMdl();

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

    //treshold for subdivision
    int max_amount_objects;
    int amount_objects;

    //internal data
    ModelLibrary_v2 * mdllib;

    Model * dbg_mdl;
    ModelLibrary * real_lib;
    QString path;

    QList<Vector3> node_bounds;



    //event stuff
    void debugMessage(QString message);
    void eventRecieved(Event e);

};

#endif // OCTTREE_H
