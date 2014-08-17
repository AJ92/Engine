#include "octtree.h"

OctTree::OctTree(int max_amount_objects)
{
    this->max_amount_objects = max_amount_objects;
    //mdllib = new ModelLibrary();
}

OctTree::OctTree(int subdiv_lvl,Vector3 pos, double node_size, int max_amount_objects)
{
    this->subdivision_level = subdiv_lvl;
    this->pos = pos;
    this->node_size = node_size;
    this->max_amount_objects = max_amount_objects;
}

OctTree::~OctTree(){
    //DESTRUCTOR... soon
}
