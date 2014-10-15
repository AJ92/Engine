/*
 * A faster OctTree in terms of inserting and removing objects ...
 * but those are not sorted and because of that slower during rendering ...
 *
 *
 * Objects are readded if their positation event is transmitted...
 *
 */
#ifndef OCTTREEFAST_H
#define OCTTREEFAST_H

#include "Event/eventlistener.h"
#include "Event/eventtransmitter.h"
#include "Math/mathematics.h"

//no model lib... we just use a simple list or hash... lets see...
#include "Graphics/Camera/frustum.h"

#include <QList>
#include <QHash>

#include "Object/SmartPointer/smartpointer.h"

#include "Math/Intersections/intersections.h"

class Event;
class CompositeObject;
class Positation;

class OctTreeFast : virtual public EventListener, virtual public EventTransmitter
{
public:
    //for root node
    OctTreeFast(int max_amount_objects);

    //for inner/leaf nodes
    OctTreeFast(int subdiv_lvl, Vector3 pos,
                double node_size, int max_amount_objects,
                SP<OctTreeFast> tree_root);
    virtual ~OctTreeFast();

    void constructNodePoints();

    int fits(SP<CompositeObject> obj);
    void subdivide();

    int addCompositeObject(SP<CompositeObject> obj);
    int addCompositeObjects(QList<SP<CompositeObject> > lib);

    int removeCompositeObject(SP<CompositeObject> obj);

    QList<SP<CompositeObject> > getCompositeObjects();

    QList<SP<OctTreeFast> > getNodesInFrustum(SP<Frustum> f);

    QString debug_string();

    enum NodeType {
        NodeRoot                    = 0x0000,
        NodeInner                   = 0x0001,
        NodeLeaf                    = 0x0002
    };

    //The event type.
    NodeType type;

    int getObjectCount();

    Vector3 getPosition();

    double getSize();

private:
    //store the tree root for fast access from inner nodes or leafs...
    SP<OctTreeFast> tree_root;

    SP<OctTreeFast> me;
    SP<EventListener> me_eventListener;

    //the subdivided "sub-cubes"
    SP<OctTreeFast> tree_northwest_high;
    SP<OctTreeFast> tree_northeast_high;
    SP<OctTreeFast> tree_southwest_high;
    SP<OctTreeFast> tree_southeast_high;

    SP<OctTreeFast> tree_northwest_low;
    SP<OctTreeFast> tree_northeast_low;
    SP<OctTreeFast> tree_southwest_low;
    SP<OctTreeFast> tree_southeast_low;

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
    QList<SP<CompositeObject> > objectLib;
    QHash<unsigned long long, SP<CompositeObject> > id_compositeobject_hash;

    QString path;

    QList<Vector3> node_bounds;
    AABB aabb;
    Sphere sphere;

    //event stuff
    void debugMessage(QString message);
    void eventRecieved(Event e);

};

#endif // OCTTREEFAST_H
