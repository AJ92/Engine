#include "octtree.h"

OctTree::OctTree(int max_amount_objects)
{
    this->max_amount_objects = max_amount_objects;
    //temporary limit...
    this->node_size = (double) 0xFFFFFFFF;
    mdllib = new ModelLibrary_v2();
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

bool OctTree::addModel(Model * mdl){
    //check if mdl center is in this node
    Vector3 mdl_pos = mdl->getPosition();
    if((mdl_pos.x()+mdl->get_size()) < (pos.x()+node_size) && (mdl_pos.x()-mdl->get_size()) > (pos.x()-node_size)){
        //inside of the X axis
        if((mdl_pos.y()+mdl->get_size()) < (pos.y()+node_size) && (mdl_pos.y()-mdl->get_size()) > (pos.y()-node_size)){
            //inside of the Y axis
            if((mdl_pos.z()+mdl->get_size()) < (pos.z()+node_size) && (mdl_pos.z()-mdl->get_size()) > (pos.z()-node_size)){
                //inside of the Z axis
                //ok looks like the model is somehow in this node

                //lets check if we need to add it or to send to our leaf nodes
                if(is_subdivided){
                    //sending to leaf nodes

                    bool r1 = tree_northwest_high->addModel(mdl);
                    bool r2 = tree_northeast_high->addModel(mdl);
                    bool r3 = tree_southwest_high->addModel(mdl);
                    bool r4 = tree_southeast_high->addModel(mdl);

                    bool r5 = tree_northwest_low->addModel(mdl);
                    bool r6 = tree_northeast_low->addModel(mdl);
                    bool r7 = tree_southwest_low->addModel(mdl);
                    bool r8 = tree_southeast_low->addModel(mdl);

                    if(r1 || r2 || r3 || r4 || r5 || r6 || r7 || r8){
                        amount_objects += 1;
                        return true;
                    }
                    return false;
                }
                else{

                    //lets add it
                    mdllib->addModel(mdl);
                    amount_objects += 1;
                    if(amount_objects > max_amount_objects){
                        subdivide();
                    }
                    return true;
                }
            }
        }
    }
    return false;
}

int OctTree::addModels(ModelLibrary_v2 * lib){

    if(is_subdivided){
        int r1 = tree_northwest_high->addModels(lib);
        int r2 = tree_northeast_high->addModels(lib);
        int r3 = tree_southwest_high->addModels(lib);
        int r4 = tree_southeast_high->addModels(lib);

        int r5 = tree_northwest_low->addModels(lib);
        int r6 = tree_northeast_low->addModels(lib);
        int r7 = tree_southwest_low->addModels(lib);
        int r8 = tree_southeast_low->addModels(lib);

        int added_c = (r1 +r2 +r3 +r4 +r5 +r6 +r7 +r8);
        amount_objects += added_c;
        return added_c;
    }


    int added_c = 0;
    QList<Model*> mdls = lib->getModels();
    QList<Model*> mdls_to_remove;
    for(int i = 0; i < mdls.size(); i++){
        bool added = addModel(mdls.at(i));
        if(added){
            added_c += 1;
            amount_objects += 1;
            mdls_to_remove.append(mdls.at(i));
        }
    }
    for(int i = 0; i < mdls_to_remove.size(); i++){
        lib->removeModel(mdls_to_remove.at(i));
    }


    if(is_subdivided){
        if(amount_objects > max_amount_objects){
            subdivide();
        }
    }

    return added_c;
}

void OctTree::subdivide(){
    double new_node_size = this->node_size/2.0;
    double new_node_pos = new_node_size/2.0;
    tree_northwest_high = new OctTree(this->subdivision_level+1,
                                      Vector3(this->pos.x()-new_node_pos,
                                              this->pos.y()+new_node_pos,
                                              this->pos.z()+new_node_pos),
                                      new_node_size,
                                      this->max_amount_objects);
    tree_northwest_high->addModels(mdllib);

    tree_northeast_high = new OctTree(this->subdivision_level+1,
                                      Vector3(this->pos.x()+new_node_pos,
                                              this->pos.y()+new_node_pos,
                                              this->pos.z()+new_node_pos),
                                      new_node_size,
                                      this->max_amount_objects);
    tree_northeast_high->addModels(mdllib);

    tree_southwest_high = new OctTree(this->subdivision_level+1,
                                      Vector3(this->pos.x()-new_node_pos,
                                              this->pos.y()-new_node_pos,
                                              this->pos.z()+new_node_pos),
                                      new_node_size,
                                      this->max_amount_objects);
    tree_southwest_high->addModels(mdllib);

    tree_southeast_high = new OctTree(this->subdivision_level+1,
                                      Vector3(this->pos.x()+new_node_pos,
                                              this->pos.y()-new_node_pos,
                                              this->pos.z()+new_node_pos),
                                      new_node_size,
                                      this->max_amount_objects);
    tree_southeast_high->addModels(mdllib);



    tree_northwest_low = new OctTree(this->subdivision_level+1,
                                     Vector3(this->pos.x()-new_node_pos,
                                             this->pos.y()+new_node_pos,
                                             this->pos.z()-new_node_pos),
                                     new_node_size,
                                     this->max_amount_objects);
    tree_northwest_low->addModels(mdllib);

    tree_northeast_low = new OctTree(this->subdivision_level+1,
                                     Vector3(this->pos.x()+new_node_pos,
                                             this->pos.y()+new_node_pos,
                                             this->pos.z()-new_node_pos),
                                     new_node_size,
                                     this->max_amount_objects);
    tree_northeast_low->addModels(mdllib);

    tree_southwest_low = new OctTree(this->subdivision_level+1,
                                     Vector3(this->pos.x()-new_node_pos,
                                             this->pos.y()-new_node_pos,
                                             this->pos.z()-new_node_pos),
                                     new_node_size,
                                     this->max_amount_objects);
    tree_southwest_low->addModels(mdllib);

    tree_southeast_low = new OctTree(this->subdivision_level+1,
                                     Vector3(this->pos.x()+new_node_pos,
                                             this->pos.y()-new_node_pos,
                                             this->pos.z()-new_node_pos),
                                     new_node_size,
                                     this->max_amount_objects);
    tree_southeast_low->addModels(mdllib);

    this->is_subdivided = true;
}
