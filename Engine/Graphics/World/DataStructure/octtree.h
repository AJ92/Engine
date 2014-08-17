#ifndef OCTTREE_H
#define OCTTREE_H

#include "Object/object.h"
#include "Math/mathematics.h"

#include "Graphics/Model/modellibrary.h"

#include <QList>

class OctTree : public Object
{
public:
    OctTree(int max_amount_objects);
    OctTree(int subdiv_lvl,Vector3 pos, double node_size, int max_amount_objects);
    ~OctTree();

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
    ModelLibrary * mdllib;

};

#endif // OCTTREE_H
