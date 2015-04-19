/*
 *  An OctTree for storing multiple types of data elements with different
 *  types of optimizations (static, dynamic models and more...)
 */

#ifndef OCTREETYPEOPTIMIZED_H
#define OCTREETYPEOPTIMIZED_H
#include "mathematics.h"

#include "Graphics/Model/modellibrary.h"
#include "Graphics/Camera/frustum.h"

#include <QList>
#include <QHash>

#include "Object/SmartPointer/smartpointer.h"

#include "Intersections/intersections.h"

#include "Object/entity.h"


class OcTreeTypeOptimized : public Component, virtual public EventListener, virtual public EventTransmitter
{
public:
    //for root node
    OcTreeTypeOptimized(int max_amount_objects);
    //for inner/leaf nodes
    OcTreeTypeOptimized(int subdiv_lvl, Vector3 pos, double node_size, int max_amount_objects);
    virtual ~OcTreeTypeOptimized();

    void constructNodePoints();

    int fits(SP<Entity> obj);
    void subdivide();

    int addEntity(SP<Entity> obj);
    int addEntities(SP<ModelLibrary_v2> lib);

    SP<ModelLibrary_v2> getModelLibrary();
    QList<SP<Entity> > getEntities();
    QList<SP<OcTreeTypeOptimized> > getNodesInFrustum(SP<Frustum> f);

    QString debug_string();

    enum NodeType {
        NodeRoot                    = 0x0000,
        NodeInner                   = 0x0001,
        NodeLeaf                    = 0x0002
    };

    enum OptimizationType {
        OptimizationStatic          = 0x0000,
        OptimizationDynamic         = 0x0001,
        OptimizationLogic           = 0x0002
    };


    int getObjectCount();
    Vector3 getPosition();
    double getSize();


    virtual void init();
    virtual void update(float mFT);

private:

    NodeType nodeType;
    OptimizationType optimizationType;

    SP<OcTreeTypeOptimized> me;
    SP<EventListener> me_eventListener;

    //the subdivided "sub-cubes"
    SP<OcTreeTypeOptimized> tree_northwest_high;
    SP<OcTreeTypeOptimized> tree_northeast_high;
    SP<OcTreeTypeOptimized> tree_southwest_high;
    SP<OcTreeTypeOptimized> tree_southeast_high;

    SP<OcTreeTypeOptimized> tree_northwest_low;
    SP<OcTreeTypeOptimized> tree_northeast_low;
    SP<OcTreeTypeOptimized> tree_southwest_low;
    SP<OcTreeTypeOptimized> tree_southeast_low;

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
    QList<SP<Entity> > entityLib;
    QHash<unsigned long long, SP<Entity> > id_compositeobject_hash;


    SP<ModelLibrary> real_lib;
    QString path;

    QList<Vector3> node_bounds;
    AABB aabb;
    Sphere sphere;


    //event stuff
    void debugMessage(QString message);
    void eventRecieved(Event e);

};

#endif // OCTREETYPEOPTIMIZED_H
