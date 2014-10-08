#include "octtreefast.h"

#include "Event/event.h"
#include "Object/compositeobject.h"
#include "Object/positation.h"



OctTreeFast::OctTreeFast(int max_amount_objects)
{
    this->subdivision_level = 0;
    this->max_amount_objects = max_amount_objects;
    this->is_subdivided = false;
    this->pos = Vector3(2.0,2.0,2.0);
    //temporary limit...
    this->node_size = 1000.0;
    objectLib.reserve(max_amount_objects);
    id_compositeobject_hash.reserve(max_amount_objects);
    amount_objects = 0;
    type = NodeRoot;
    constructNodePoints();
    tree_root = SP<OctTreeFast>(this);

    me = tree_root;
    me_eventListener = SP<EventListener> (this);
}

OctTreeFast::OctTreeFast(int subdiv_lvl, Vector3 pos,
                         double node_size, int max_amount_objects,
                         SP<OctTreeFast> tree_root)
{
    this->subdivision_level = subdiv_lvl;
    this->is_subdivided = false;
    this->pos = pos;
    this->node_size = node_size;
    this->max_amount_objects = max_amount_objects;
    objectLib.reserve(max_amount_objects);
    id_compositeobject_hash.reserve(max_amount_objects);
    amount_objects = 0;
    type = NodeLeaf;
    constructNodePoints();
    this->tree_root = tree_root;

    me = SP<OctTreeFast>(this);
    me_eventListener = SP<EventListener> (this);
}

void OctTreeFast::constructNodePoints(){
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

OctTreeFast::~OctTreeFast(){
    //DESTRUCTOR... soon
    qDebug("OctTreeFast::~OctTreeFast");
}

QList<SP<OctTreeFast> > OctTreeFast::getNodesInFrustum(SP<Frustum> f){
    QList<SP<OctTreeFast> > treeList;

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


//might need to check if it intersect the bounds ... for refitting...
int OctTreeFast::fits(SP<CompositeObject> obj){

    if(obj == 0){
        qDebug("[WARNING] OctTree::fits(CompositeObject * obj) : no CompositeObject ...");
        return false;
    }


    Sphere mdl_sphere = obj->getPositation()->getSphere();

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
    SP<Positation> posi = obj->getPositation();
    Vector3 obj_pos = posi->getPosition();
    if((obj_pos.x()+posi->get_size_scaled()) <= (pos.x()+node_size) &&
       (obj_pos.x()-posi->get_size_scaled()) >= (pos.x()-node_size)){
        //inside of the X axis
        if((obj_pos.y()+posi->get_size_scaled()) <= (pos.y()+node_size) &&
           (obj_pos.y()-posi->get_size_scaled()) >= (pos.y()-node_size)){
            //inside of the Y axis
            if((obj_pos.z()+posi->get_size_scaled()) <= (pos.z()+node_size) &&
               (obj_pos.z()-posi->get_size_scaled()) >= (pos.z()-node_size)){
                //model fits in this node
                return true;
            }
        }
    }
    return false;
    */
}

QString OctTreeFast::debug_string(){
    QString debug_str = "OctTreeFast lvl: ";

    if(amount_objects>=0){
        debug_str = debug_str + QString::number(subdivision_level) + "  --  " +
                QString::number(objectLib.size()) + "/" +
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


int OctTreeFast::addCompositeObject(SP<CompositeObject> obj){
    if(obj == 0){
        debugMessage("OctTreeFast::addCompositeObject(CompositeObject * obj) : obj is null...");
    }

    qDebug("adding object to octtreefast");

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

        int result_added = 0;

        //model fits once or does not fit at all...
        if(fit_count < 2){
            //lets check where it fitted and add it there
            if(f1 == 1){
                result_added += tree_northwest_high->addCompositeObject(obj);
            }
            else if(f2 == 1){
                result_added += tree_northeast_high->addCompositeObject(obj);
            }
            else if(f3 == 1){
                result_added += tree_southwest_high->addCompositeObject(obj);
            }
            else if(f4 == 1){
                result_added += tree_southeast_high->addCompositeObject(obj);
            }
            else if(f5 == 1){
                result_added += tree_northwest_low->addCompositeObject(obj);
            }
            else if(f6 == 1){
                result_added += tree_northeast_low->addCompositeObject(obj);
            }
            else if(f7 == 1){
                result_added += tree_southwest_low->addCompositeObject(obj);
            }
            else if(f8 == 1){
                result_added += tree_southeast_low->addCompositeObject(obj);
            }
        }
        //ok the obj obviously fits into more than one node... lets add it to the parent node...
        else{
            result_added += 1;
            objectLib.append(obj);
            //register the object... this node becomes a listener for its events...
            obj->addListener(me_eventListener);
        }

        //add model to hash if it fitted this node or its child
        if(result_added > 0){
            id_compositeobject_hash.insert(obj->EventTransmitter::id(),obj);
        }

        amount_objects += result_added;
        return result_added;

    }

    // just add the model, my parent node has checked for me,
    // if the model fits inside me...


    objectLib.append(obj);
    //register the object... this node becomes a listener for its events...
    obj->addListener(me_eventListener);

    id_compositeobject_hash.insert(obj->EventTransmitter::id(),obj);

    amount_objects += 1;
    if(amount_objects > max_amount_objects){
        subdivide();
    }
    return 1;

}

int OctTreeFast::addCompositeObjects(QList<SP<CompositeObject> > lib){

    int added_count = 0;

    QList<SP<CompositeObject> > objs = lib;

    for(int i = 0; i < objs.size(); i++){
        if(fits(objs.at(i))){
            int added = addCompositeObject(objs.at(i));
            amount_objects += added;
            added_count += added;
        }
    }
    return added_count;
}

int OctTreeFast::removeCompositeObject(SP<CompositeObject> obj){
    //should work, that we only save unique objects here...
    bool removed = false;
    if(objectLib.contains(obj)){
        objectLib.removeOne(obj);
        removed = true;
        obj->removeListener(me_eventListener);
        amount_objects -= 1;

        id_compositeobject_hash.remove(obj->EventTransmitter::id());
    }
    return removed;
}

QList<SP<CompositeObject> > OctTreeFast::getCompositeObjects(){
    return objectLib;
}


void OctTreeFast::subdivide(){
    QList<SP<CompositeObject> > objectLib_old = objectLib;
    objectLib.clear();

    //clear the listeners...
    for(int i = 0; i < objectLib_old.size(); i++){
        objectLib_old[i]->removeListener(me_eventListener);
    }

    amount_objects = 0;

    double new_node_size = this->node_size/2.0;
    double new_node_pos = new_node_size;

    tree_northwest_high = SP<OctTreeFast>(new OctTreeFast(this->subdivision_level+1,
                                          Vector3(this->pos.x()-new_node_pos,
                                                  this->pos.y()+new_node_pos,
                                                  this->pos.z()+new_node_pos),
                                          new_node_size,
                                          this->max_amount_objects,
                                          this->tree_root));
    //amount_objects += tree_northwest_high->addModels(old_lib);

    tree_northeast_high = SP<OctTreeFast>(new OctTreeFast(this->subdivision_level+1,
                                          Vector3(this->pos.x()+new_node_pos,
                                                  this->pos.y()+new_node_pos,
                                                  this->pos.z()+new_node_pos),
                                          new_node_size,
                                          this->max_amount_objects,
                                          this->tree_root));
    //amount_objects += tree_northeast_high->addModels(old_lib);

    tree_southwest_high = SP<OctTreeFast>(new OctTreeFast(this->subdivision_level+1,
                                          Vector3(this->pos.x()-new_node_pos,
                                                  this->pos.y()-new_node_pos,
                                                  this->pos.z()+new_node_pos),
                                          new_node_size,
                                          this->max_amount_objects,
                                          this->tree_root));
    //amount_objects += tree_southwest_high->addModels(old_lib);

    tree_southeast_high = SP<OctTreeFast>(new OctTreeFast(this->subdivision_level+1,
                                          Vector3(this->pos.x()+new_node_pos,
                                                  this->pos.y()-new_node_pos,
                                                  this->pos.z()+new_node_pos),
                                          new_node_size,
                                          this->max_amount_objects,
                                          this->tree_root));
    //amount_objects += tree_southeast_high->addModels(old_lib);



    tree_northwest_low = SP<OctTreeFast>(new OctTreeFast(this->subdivision_level+1,
                                         Vector3(this->pos.x()-new_node_pos,
                                                 this->pos.y()+new_node_pos,
                                                 this->pos.z()-new_node_pos),
                                         new_node_size,
                                         this->max_amount_objects,
                                         this->tree_root));
    //amount_objects += tree_northwest_low->addModels(old_lib);

    tree_northeast_low = SP<OctTreeFast>(new OctTreeFast(this->subdivision_level+1,
                                         Vector3(this->pos.x()+new_node_pos,
                                                 this->pos.y()+new_node_pos,
                                                 this->pos.z()-new_node_pos),
                                         new_node_size,
                                         this->max_amount_objects,
                                         this->tree_root));
    //amount_objects += tree_northeast_low->addModels(old_lib);

    tree_southwest_low = SP<OctTreeFast>(new OctTreeFast(this->subdivision_level+1,
                                         Vector3(this->pos.x()-new_node_pos,
                                                 this->pos.y()-new_node_pos,
                                                 this->pos.z()-new_node_pos),
                                         new_node_size,
                                         this->max_amount_objects,
                                         this->tree_root));
    //amount_objects += tree_southwest_low->addModels(old_lib);

    tree_southeast_low = SP<OctTreeFast>(new OctTreeFast(this->subdivision_level+1,
                                         Vector3(this->pos.x()+new_node_pos,
                                                 this->pos.y()-new_node_pos,
                                                 this->pos.z()-new_node_pos),
                                         new_node_size,
                                         this->max_amount_objects,
                                         this->tree_root));
    //amount_objects += tree_southeast_low->addModels(old_lib);

    this->is_subdivided = true;

    if(type != NodeRoot){
        type = NodeInner;
    }

    amount_objects += addCompositeObjects(objectLib_old);
}


//EVENT LISTENER
//do not invoke the parents method...
void OctTreeFast::eventRecieved(Event e){
    if(e.type == Event::EventCompositeObjectMoved || e.type == Event::EventCompositeObjectScaled){
        //the object changed it's size or moved...
        //check if it still fits in this node...
        //if not, remove it and add it to the root node,
        //so it can add it to the node it fits...

        debugMessage("OctTreeFast: removing object and inserting it into root node...");

        SP<CompositeObject> obj = e.compositeObject->getCompositeObject();
     //   int fitting = 0;
     //   fitting = fits(obj);
     //   if(fitting == 0){
            qDebug("OctTreeFast: removing object and inserting it into root node...");

            removeCompositeObject(obj);
            //obj->removeListener(me_eventListener);
            tree_root->addCompositeObject(obj);
     //   }
     //   qDebug("still fits");
        return;
    }
    if(e.type == Event::EventCompositeObjectRemoved || e.type == Event::EventCompositeObjectDeleted){
        //never tested...
        SP<CompositeObject> obj = e.compositeObject->getCompositeObject();
        removeCompositeObject(obj);
        return;
    }
}

void OctTreeFast::debugMessage(QString message){
    Event e;
    e.type = Event::EventDebuggerMessage;
    e.debugger = SP<EventDebugger> (new EventDebugger(message));
    this->transmit(e);
}
