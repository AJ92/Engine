#include "octtree.h"

#include "Event/event.h"
#include "Object/compositeobject.h"
#include "Object/positation.h"

OctTree::OctTree(int max_amount_objects)
{
    this->subdivision_level = 0;
    this->max_amount_objects = max_amount_objects;
    this->is_subdivided = false;
    this->pos = Vector3(0.0,0.0,0.0);
    //temporary limit...
    this->node_size = 1000.0;
    mdllib = new ModelLibrary_v2(max_amount_objects,max_amount_objects);
    mdllib->initialize();
    id_compositeobject_hash.reserve(max_amount_objects);
    amount_objects = 0;
    type = NodeRoot;
    constructNodePoints();
}

OctTree::OctTree(int subdiv_lvl,Vector3 pos, double node_size, int max_amount_objects)
{
    this->subdivision_level = subdiv_lvl;
    this->is_subdivided = false;
    this->pos = pos;
    this->node_size = node_size;
    this->max_amount_objects = max_amount_objects;
    mdllib = new ModelLibrary_v2(max_amount_objects,max_amount_objects);
    mdllib->initialize();
    id_compositeobject_hash.reserve(max_amount_objects);
    amount_objects = 0;
    type = NodeLeaf;
    constructNodePoints();
}

void OctTree::constructNodePoints(){
    Vector3 p1(pos.x()+node_size,pos.y()+node_size,pos.z()+node_size);
    node_bounds.append(p1);

    Vector3 p2(pos.x()-node_size,pos.y()+node_size,pos.z()+node_size);
    node_bounds.append(p2);

    Vector3 p3(pos.x()-node_size,pos.y()-node_size,pos.z()+node_size);
    node_bounds.append(p3);

    Vector3 p4(pos.x()+node_size,pos.y()-node_size,pos.z()+node_size);
    node_bounds.append(p4);

    Vector3 p5(pos.x()+node_size,pos.y()+node_size,pos.z()-node_size);
    node_bounds.append(p5);

    Vector3 p6(pos.x()-node_size,pos.y()+node_size,pos.z()-node_size);
    node_bounds.append(p6);

    Vector3 p7(pos.x()-node_size,pos.y()-node_size,pos.z()-node_size);
    node_bounds.append(p7);

    Vector3 p8(pos.x()+node_size,pos.y()-node_size,pos.z()-node_size);
    node_bounds.append(p8);

}

OctTree::~OctTree(){
    //DESTRUCTOR... soon
}

QList<OctTree* > OctTree::getNodesInFrustum(Frustum * f){
    QList<OctTree *> treeList;

    for(int i = 0; i < node_bounds.size(); i++){
        if(f->pointInFrustum(node_bounds.at(i)) == Frustum::Inside){
            //lets add this leaf node, might be root aswell...
            if(is_subdivided == false){
                treeList.append(this);
            }
            //lets get subnodes...
            else{
                //unfortunatly inner nodes can have models as well...
                //add all the OctTree nodes to the list..

                treeList.append(this);

                treeList.append(tree_northwest_high->getNodesInFrustum(f));
                treeList.append(tree_northeast_high->getNodesInFrustum(f));
                treeList.append(tree_southwest_high->getNodesInFrustum(f));
                treeList.append(tree_southeast_high->getNodesInFrustum(f));

                treeList.append(tree_northwest_low->getNodesInFrustum(f));
                treeList.append(tree_northeast_low->getNodesInFrustum(f));
                treeList.append(tree_southwest_low->getNodesInFrustum(f));
                treeList.append(tree_southeast_low->getNodesInFrustum(f));
            }
            //enough if one point is inside of the frustum
            break;
        }
    }

    return treeList;
}

int OctTree::fits(CompositeObject * obj){

    if(obj == 0){
        qDebug("[WARNING] OctTree::fits(CompositeObject * obj) : no CompositeObject ...");
        return false;
    }

    Positation * posi = obj->getPositation();
    Vector3 mdl_pos = posi->getPosition();
    if((mdl_pos.x()+posi->get_size()) <= (pos.x()+node_size) &&
       (mdl_pos.x()-posi->get_size()) >= (pos.x()-node_size)){
        //inside of the X axis
        if((mdl_pos.y()+posi->get_size()) <= (pos.y()+node_size) &&
           (mdl_pos.y()-posi->get_size()) >= (pos.y()-node_size)){
            //inside of the Y axis
            if((mdl_pos.z()+posi->get_size()) <= (pos.z()+node_size) &&
               (mdl_pos.z()-posi->get_size()) >= (pos.z()-node_size)){
                //model fits in this node
                return true;
            }
        }
    }
    return false;
}

QString OctTree::debug_string(){
    QString debug_str = "OctTree lvl: ";

    if(amount_objects>=0){
        debug_str = debug_str + QString::number(subdivision_level) + "  --  " +
                QString::number(mdllib->getModels().size()) + "/" +
                QString::number(max_amount_objects) + "\n";
        if(is_subdivided){

            debug_str = debug_str + tree_northwest_high->debug_string();
            debug_str = debug_str + tree_northeast_high->debug_string();
            debug_str = debug_str + tree_southwest_high->debug_string();
            debug_str = debug_str + tree_southeast_high->debug_string();

            debug_str = debug_str + tree_northwest_low->debug_string();
            debug_str = debug_str + tree_northeast_low->debug_string();
            debug_str = debug_str + tree_southwest_low->debug_string();
            debug_str = debug_str + tree_southeast_low->debug_string();
        }
    }
    else{
        debug_str = "";
    }
    return debug_str;
}


int OctTree::addModel(CompositeObject * mdl){

    //lets check if we need to add it or to send to our leaf nodes
    if(is_subdivided){
        //sending to leaf nodes

        //we are now a parent node and we check ...

        int f1 = tree_northwest_high->fits(mdl);
        int f2 = tree_northeast_high->fits(mdl);
        int f3 = tree_southwest_high->fits(mdl);
        int f4 = tree_southeast_high->fits(mdl);

        int f5 = tree_northwest_low->fits(mdl);
        int f6 = tree_northeast_low->fits(mdl);
        int f7 = tree_southwest_low->fits(mdl);
        int f8 = tree_southeast_low->fits(mdl);

        int fit_count = f1 + f2 + f3 + f4 + f5 + f6 + f7 + f8;

        int result_added = 0;

        //model fits once or does not fit at all...
        if(fit_count < 2){
            //lets check where it fitted and add it there
            if(f1 == 1){
                result_added += tree_northwest_high->addModel(mdl);
            }
            else if(f2 == 1){
                result_added += tree_northeast_high->addModel(mdl);
            }
            else if(f3 == 1){
                result_added += tree_southwest_high->addModel(mdl);
            }
            else if(f4 == 1){
                result_added += tree_southeast_high->addModel(mdl);
            }
            else if(f5 == 1){
                result_added += tree_northwest_low->addModel(mdl);
            }
            else if(f6 == 1){
                result_added += tree_northeast_low->addModel(mdl);
            }
            else if(f7 == 1){
                result_added += tree_southwest_low->addModel(mdl);
            }
            else if(f8 == 1){
                result_added += tree_southeast_low->addModel(mdl);
            }
        }
        //ok the model obviously fits into more than one node... lets add it to the parent node...
        else{
            result_added += 1;
            mdllib->addModel(mdl->getModel());
        }

        //add model to hash if it fitted this node or its child
        if(result_added > 0){
            id_compositeobject_hash.insert(mdl->id(),mdl);
        }

        amount_objects += result_added;
        return result_added;

    }

    // just add the model, my parent node has checked for me,
    // if the model fits inside me...

    if(mdl->getModel()->getParentCompositeObject() == 0){
        qDebug("[WARNING] OctTree::addModel(CompositeObject * mdl) : no CompositeObject ...");
    }

    mdllib->addModel(mdl->getModel());
    id_compositeobject_hash.insert(mdl->id(),mdl);

    amount_objects += 1;
    if(amount_objects > max_amount_objects){
        subdivide();
    }
    return 1;

}

int OctTree::addModels(ModelLibrary_v2 * lib){

    int added_count = 0;

    QList<Model*> mdls = lib->getModels();

    for(int i = 0; i < mdls.size(); i++){
        if(fits(mdls.at(i)->getParentCompositeObject())){
            int added = addModel(mdls.at(i)->getParentCompositeObject());
            amount_objects += added;
            added_count += added;
        }
    }
    return added_count;
}

void OctTree::subdivide(){

    ModelLibrary_v2 * old_lib = mdllib;
    mdllib = new ModelLibrary_v2(max_amount_objects,max_amount_objects);
    mdllib->initialize();

    amount_objects = 0;

    double new_node_size = this->node_size/2.0;
    double new_node_pos = new_node_size;



    tree_northwest_high = new OctTree(this->subdivision_level+1,
                                      Vector3(this->pos.x()-new_node_pos,
                                              this->pos.y()+new_node_pos,
                                              this->pos.z()+new_node_pos),
                                      new_node_size,
                                      this->max_amount_objects);
    //amount_objects += tree_northwest_high->addModels(old_lib);

    tree_northeast_high = new OctTree(this->subdivision_level+1,
                                      Vector3(this->pos.x()+new_node_pos,
                                              this->pos.y()+new_node_pos,
                                              this->pos.z()+new_node_pos),
                                      new_node_size,
                                      this->max_amount_objects);
    //amount_objects += tree_northeast_high->addModels(old_lib);

    tree_southwest_high = new OctTree(this->subdivision_level+1,
                                      Vector3(this->pos.x()-new_node_pos,
                                              this->pos.y()-new_node_pos,
                                              this->pos.z()+new_node_pos),
                                      new_node_size,
                                      this->max_amount_objects);
    //amount_objects += tree_southwest_high->addModels(old_lib);

    tree_southeast_high = new OctTree(this->subdivision_level+1,
                                      Vector3(this->pos.x()+new_node_pos,
                                              this->pos.y()-new_node_pos,
                                              this->pos.z()+new_node_pos),
                                      new_node_size,
                                      this->max_amount_objects);
    //amount_objects += tree_southeast_high->addModels(old_lib);



    tree_northwest_low = new OctTree(this->subdivision_level+1,
                                     Vector3(this->pos.x()-new_node_pos,
                                             this->pos.y()+new_node_pos,
                                             this->pos.z()-new_node_pos),
                                     new_node_size,
                                     this->max_amount_objects);
    //amount_objects += tree_northwest_low->addModels(old_lib);

    tree_northeast_low = new OctTree(this->subdivision_level+1,
                                     Vector3(this->pos.x()+new_node_pos,
                                             this->pos.y()+new_node_pos,
                                             this->pos.z()-new_node_pos),
                                     new_node_size,
                                     this->max_amount_objects);
    //amount_objects += tree_northeast_low->addModels(old_lib);

    tree_southwest_low = new OctTree(this->subdivision_level+1,
                                     Vector3(this->pos.x()-new_node_pos,
                                             this->pos.y()-new_node_pos,
                                             this->pos.z()-new_node_pos),
                                     new_node_size,
                                     this->max_amount_objects);
    //amount_objects += tree_southwest_low->addModels(old_lib);

    tree_southeast_low = new OctTree(this->subdivision_level+1,
                                     Vector3(this->pos.x()+new_node_pos,
                                             this->pos.y()-new_node_pos,
                                             this->pos.z()-new_node_pos),
                                     new_node_size,
                                     this->max_amount_objects);
    //amount_objects += tree_southeast_low->addModels(old_lib);

    this->is_subdivided = true;

    if(type != NodeRoot){
        type = NodeInner;
    }

    amount_objects += addModels(old_lib);


    ////////////////////////////////////////////////////////////////////////////////////////////
    ///
    /// NEED TO DESTROY OLD MODELLIBRARY_V2
    ///
    /// old_lib
}



//EVENT LISTENER
//do not invoke the parents method...
void OctTree::eventRecieved(Event e){
    if(e.type == Event::EventDebuggerMessage){
        //we dont need that type of messages here...
        //we discard it... poor event :(
        return;
    }

}

void OctTree::debugMessage(QString message){
    Event e;
    e.type = Event::EventDebuggerMessage;
    e.debugger = new EventDebugger(message);
    this->transmit(e);
}
