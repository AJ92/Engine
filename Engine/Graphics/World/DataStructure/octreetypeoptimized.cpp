#include "octreetypeoptimized.h"

#include "Event/event.h"
#include "Object/compositeobject.h"
#include "Object/positation.h"

OcTreeTypeOptimized::OcTreeTypeOptimized(int max_amount_objects, OcTreeTypeOptimized::OptimizationType type)
{
    this->optimizationType = type;
    this->subdivision_level = 0;
    this->max_amount_objects = max_amount_objects;
    this->is_subdivided = false;
    this->pos = Vector3(2.0,2.0,2.0);
    //temporary limit...
    this->node_size = 99999999.0;
    mdllib = SP<ModelLibrary_v2>(new ModelLibrary_v2(max_amount_objects,max_amount_objects));
    mdllib->initialize();
    id_compositeobject_hash.reserve(max_amount_objects);
    amount_objects = 0;
    nodeType = NodeRoot;
    constructNodePoints();

    me = SP<OcTreeTypeOptimized>(this);
    me_eventListener = SP<EventListener> (this);
}

OcTreeTypeOptimized::OcTreeTypeOptimized(int subdiv_lvl,Vector3 pos, double node_size, int max_amount_objects, OcTreeTypeOptimized::OptimizationType type)
{
    this->optimizationType = type;
    this->subdivision_level = subdiv_lvl;
    this->is_subdivided = false;
    this->pos = pos;
    this->node_size = node_size;
    this->max_amount_objects = max_amount_objects;
    mdllib = SP<ModelLibrary_v2>(new ModelLibrary_v2(max_amount_objects,max_amount_objects));
    mdllib->initialize();
    id_compositeobject_hash.reserve(max_amount_objects);
    amount_objects = 0;
    nodeType = NodeLeaf;
    constructNodePoints();

    me = SP<OcTreeTypeOptimized>(this);
    me_eventListener = SP<EventListener> (this);
}

void OcTreeTypeOptimized::constructNodePoints(){
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

    spherical_node_size = pos.distance(p1);

    //construct AABB
    //p1 and p7 should do it...

    aabb = AABB(p7, p1);
    sphere = Sphere(pos, spherical_node_size);


}

OcTreeTypeOptimized::~OcTreeTypeOptimized(){
    //DESTRUCTOR... soon
    //qDebug("OctTree::~OctTree");
}

OcTreeTypeOptimized::OptimizationType OcTreeTypeOptimized::getOptimizationType(){
    return optimizationType;
}

QList<SP<OcTreeTypeOptimized> > OcTreeTypeOptimized::getNodesInFrustum(SP<Frustum> f){
    QList<SP<OcTreeTypeOptimized> > treeList;


    //check if points of the node are inside of the frustum...
    int check = f->sphereInFrustum(pos, spherical_node_size);
    if(check == Frustum::Inside || check == Frustum::Intersect){
        //lets add this leaf node, might be root aswell...
        if(is_subdivided == false){
            treeList.append(me);
        }
        //lets get subnodes...
        else{
            //unfortunatly inner nodes can have models as well...
            //add all the OctTree nodes to the list..

            treeList.append(me);

            treeList.append(tree_northwest_high->getNodesInFrustum(f));
            treeList.append(tree_northeast_high->getNodesInFrustum(f));
            treeList.append(tree_southwest_high->getNodesInFrustum(f));
            treeList.append(tree_southeast_high->getNodesInFrustum(f));

            treeList.append(tree_northwest_low->getNodesInFrustum(f));
            treeList.append(tree_northeast_low->getNodesInFrustum(f));
            treeList.append(tree_southwest_low->getNodesInFrustum(f));
            treeList.append(tree_southeast_low->getNodesInFrustum(f));
        }
    }
    return treeList;
}

int OcTreeTypeOptimized::fits(SP<Entity> obj){

    if(obj == 0){
        qDebug("[WARNING] int OcTreeTypeOptimized::fits(SP<Entity> obj) : no Entity ...");
        return 0;
    }

    if(!obj->hasComponent<Positation>()){
        qDebug("[WARNING] int OcTreeTypeOptimized::fits(SP<Entity> obj) : no Positation Component in Entity ...");
        return 0;
    }


    Sphere mdl_sphere = obj->getComponent<Positation>()->getSphere();

    //check if the center of bounding sphere is inside the octree node
    if(Intersections::pointInAABB(mdl_sphere.getPos(),aabb)){
        return 1;
    }
    if(Intersections::sphereAABBIntersection(mdl_sphere,aabb)){
        return 1;
    }
    return 0;

    //point in BOX
    /*
    double size_scaled = 0.0;//posi->get_size_scaled();

    if((mdl_pos.x()+size_scaled) <= (pos.x()+node_size) &&
       (mdl_pos.x()-size_scaled) >= (pos.x()-node_size)){
        //inside of the X axis
        if((mdl_pos.y()+size_scaled) <= (pos.y()+node_size) &&
           (mdl_pos.y()-size_scaled) >= (pos.y()-node_size)){
            //inside of the Y axis
            if((mdl_pos.z()+size_scaled) <= (pos.z()+node_size) &&
               (mdl_pos.z()-size_scaled) >= (pos.z()-node_size)){
                //model fits in this node
                return true;
            }
        }
    }
    return false;
    */
}

QString OcTreeTypeOptimized::debug_string(){
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

int OcTreeTypeOptimized::getObjectCount(){
    return entityLib.size();
}

Vector3 OcTreeTypeOptimized::getPosition(){
    return pos;
}

double OcTreeTypeOptimized::getSize(){
    return node_size;
}


void OcTreeTypeOptimized::init(){

}

void OcTreeTypeOptimized::update(float mFT){

}


int OcTreeTypeOptimized::addEntity(SP<Entity> obj){

    //qDebug("adding to octree...");



    if(obj->hasComponent<Model>()){
        if(!obj->getComponent<Model>()->isReadyToRender()){
            debugMessage("OctTree::addEntity(SP<Entity> obj) : model of Enitity not ready...");
            qDebug("    model not ready yet...");
        }
    }
    else{
        debugMessage("OctTree::addEntity(SP<Entity> obj) : Enitity has no MODEL !!!! ...");
        qDebug("    no model...");
    }

    //lets check if we need to add it or to send to our leaf nodes
    if(is_subdivided){
        //sending to leaf nodes

        //we are now a parent node and we check ...

        int f1 = tree_northwest_high->fits(obj);
        int f2 = tree_northeast_high->fits(obj);
        int f3 = tree_southwest_high->fits(obj);
        int f4 = tree_southeast_high->fits(obj);

        int f5 = tree_northwest_low->fits(obj);
        int f6 = tree_northeast_low->fits(obj);
        int f7 = tree_southwest_low->fits(obj);
        int f8 = tree_southeast_low->fits(obj);

        int fit_count = f1 + f2 + f3 + f4 + f5 + f6 + f7 + f8;

        //qDebug("Fits:");
        //qDebug(QString::number(fit_count).toUtf8());

        int result_added = 0;

        //model fits once or does not fit at all...
        if(fit_count < 2){
            //lets check where it fitted and add it there
            if(f1 == 1){
                result_added += tree_northwest_high->addEntity(obj);
            }
            else if(f2 == 1){
                result_added += tree_northeast_high->addEntity(obj);
            }
            else if(f3 == 1){
                result_added += tree_southwest_high->addEntity(obj);
            }
            else if(f4 == 1){
                result_added += tree_southeast_high->addEntity(obj);
            }
            else if(f5 == 1){
                result_added += tree_northwest_low->addEntity(obj);
            }
            else if(f6 == 1){
                result_added += tree_northeast_low->addEntity(obj);
            }
            else if(f7 == 1){
                result_added += tree_southwest_low->addEntity(obj);
            }
            else if(f8 == 1){
                result_added += tree_southeast_low->addEntity(obj);
            }
        }
        //ok the obj obviously fits into more than one node... lets add it to the parent node...
        else{
            result_added += 1;
            //if is has a model...
            //TODO: adjust the mdllib to load entities...
            mdllib->addEntity(obj);
        }

        //add model to hash if it fitted this node or its child
        if(result_added > 0){
            id_compositeobject_hash.insert(obj->id(),obj);
        }

        amount_objects += result_added;
        //qDebug( QString::number(amount_objects).toUtf8());
        return result_added;

    }

    // just add the model, my parent node has checked for me,
    // if the model fits inside me...


    //TODO: fix mdl lib to load entities...
    mdllib->addEntity(obj);
    id_compositeobject_hash.insert(obj->id(),obj);

    amount_objects += 1;
    if(amount_objects > max_amount_objects){
        subdivide();
    }
    debug_string();
    //qDebug( QString::number(amount_objects).toUtf8());
    return 1;

}

int OcTreeTypeOptimized::addEntities(SP<ModelLibrary_v2> lib){

    //qDebug("ADDING LIB to OctTree");

    int added_count = 0;

    QList<SP<Entity> > objs = lib->getEntities();

    for(int i = 0; i < objs.size(); i++){
        if(fits(objs.at(i))){
            int added = addEntity(objs.at(i));
            amount_objects += added;
            added_count += added;
        }
    }
    return added_count;
}

SP<ModelLibrary_v2> OcTreeTypeOptimized::getModelLibrary(){
    return mdllib;
}

QList<SP<Entity> > OcTreeTypeOptimized::getEntities(){
    return entityLib;
}

void OcTreeTypeOptimized::subdivide(){

    qDebug("OcTreeTypeOptimized::subdivide()");

    SP<ModelLibrary_v2> old_lib = mdllib;
    mdllib = SP<ModelLibrary_v2>(new ModelLibrary_v2(max_amount_objects,max_amount_objects));
    mdllib->initialize();

    amount_objects = 0;

    double new_node_size = this->node_size/2.0;
    double new_node_pos = new_node_size;



    tree_northwest_high = SP<OcTreeTypeOptimized>(new OcTreeTypeOptimized(this->subdivision_level+1,
                                      Vector3(this->pos.x()-new_node_pos,
                                              this->pos.y()+new_node_pos,
                                              this->pos.z()+new_node_pos),
                                      new_node_size,
                                      this->max_amount_objects,
                                      this->optimizationType));
    //amount_objects += tree_northwest_high->addModels(old_lib);

    tree_northeast_high = SP<OcTreeTypeOptimized>(new OcTreeTypeOptimized(this->subdivision_level+1,
                                      Vector3(this->pos.x()+new_node_pos,
                                              this->pos.y()+new_node_pos,
                                              this->pos.z()+new_node_pos),
                                      new_node_size,
                                      this->max_amount_objects,
                                      this->optimizationType));
    //amount_objects += tree_northeast_high->addModels(old_lib);

    tree_southwest_high = SP<OcTreeTypeOptimized>(new OcTreeTypeOptimized(this->subdivision_level+1,
                                      Vector3(this->pos.x()-new_node_pos,
                                              this->pos.y()-new_node_pos,
                                              this->pos.z()+new_node_pos),
                                      new_node_size,
                                      this->max_amount_objects,
                                      this->optimizationType));
    //amount_objects += tree_southwest_high->addModels(old_lib);

    tree_southeast_high = SP<OcTreeTypeOptimized>(new OcTreeTypeOptimized(this->subdivision_level+1,
                                      Vector3(this->pos.x()+new_node_pos,
                                              this->pos.y()-new_node_pos,
                                              this->pos.z()+new_node_pos),
                                      new_node_size,
                                      this->max_amount_objects,
                                      this->optimizationType));
    //amount_objects += tree_southeast_high->addModels(old_lib);



    tree_northwest_low = SP<OcTreeTypeOptimized>(new OcTreeTypeOptimized(this->subdivision_level+1,
                                     Vector3(this->pos.x()-new_node_pos,
                                             this->pos.y()+new_node_pos,
                                             this->pos.z()-new_node_pos),
                                     new_node_size,
                                     this->max_amount_objects,
                                     this->optimizationType));
    //amount_objects += tree_northwest_low->addModels(old_lib);

    tree_northeast_low = SP<OcTreeTypeOptimized>(new OcTreeTypeOptimized(this->subdivision_level+1,
                                     Vector3(this->pos.x()+new_node_pos,
                                             this->pos.y()+new_node_pos,
                                             this->pos.z()-new_node_pos),
                                     new_node_size,
                                     this->max_amount_objects,
                                     this->optimizationType));
    //amount_objects += tree_northeast_low->addModels(old_lib);

    tree_southwest_low = SP<OcTreeTypeOptimized>(new OcTreeTypeOptimized(this->subdivision_level+1,
                                     Vector3(this->pos.x()-new_node_pos,
                                             this->pos.y()-new_node_pos,
                                             this->pos.z()-new_node_pos),
                                     new_node_size,
                                     this->max_amount_objects,
                                     this->optimizationType));
    //amount_objects += tree_southwest_low->addModels(old_lib);

    tree_southeast_low = SP<OcTreeTypeOptimized>(new OcTreeTypeOptimized(this->subdivision_level+1,
                                     Vector3(this->pos.x()+new_node_pos,
                                             this->pos.y()-new_node_pos,
                                             this->pos.z()-new_node_pos),
                                     new_node_size,
                                     this->max_amount_objects,
                                     this->optimizationType));
    //amount_objects += tree_southeast_low->addModels(old_lib);

    this->is_subdivided = true;

    if(nodeType != NodeRoot){
        nodeType = NodeInner;
    }

    amount_objects += addEntities(old_lib);
    old_lib->clearLib();


    ////////////////////////////////////////////////////////////////////////////////////////////
    ///
    /// NEED TO DESTROY OLD MODELLIBRARY_V2
    ///
    /// old_lib
}



//EVENT LISTENER
//do not invoke the parents method...
void OcTreeTypeOptimized::eventRecieved(Event e){
    if(e.type == Event::EventDebuggerMessage){
        //we dont need that type of messages here...
        //we discard it... poor event :(
        return;
    }

}

void OcTreeTypeOptimized::debugMessage(QString message){
    Event e;
    e.type = Event::EventDebuggerMessage;
    e.debugger = SP<EventDebugger> (new EventDebugger(message));
    this->transmit(e);
}
