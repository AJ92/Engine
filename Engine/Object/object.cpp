#include "object.h"


//init the next_id var...
unsigned long long Object::static_id = 0;
std::vector<unsigned long long> Object::unused_ids;


/*!
  Constructs an Object with an unique identifier.
  */
Object::Object():
    my_id(next_id())
{

}

/*!
  Destroys the Object and puts the used ID into the unused ID vector.
  */
Object::~Object(){
    //maybe after a while this can grow huge... so might think about cleaning it up after some time...
    for(unsigned int i = 0; i < unused_ids.size(); i++){
        if(unused_ids[i] == my_id){
           return;
        }
    }
    unused_ids.push_back(my_id);
}

/*!
  Returns the identifier that was constructed during object creation.
  */
unsigned long long Object::id() const{
    return my_id;
}

/*!
  "Generates" the identifier or takes an unused one from the vector. Is used during construction.

  \sa Object()
  */
unsigned long long Object::next_id(){
    if(unused_ids.size() > 0){
        //pop back and return it
        unsigned long long reuse_id = unused_ids.back();
        unused_ids.pop_back();
        return reuse_id;
    }

    static_id++;
    return static_id;
}

/*!
  Checks if the \a obj is equals itself.

  Can be overloaded...
  */
bool Object::equal(const Object &obj) const{
    if(this->my_id == obj.id()){
        return true;
    }
    return false;
}

/*!
  Returns the object's identifier as a QString.

  Can be overloaded...
  */
QString Object::to_string(){
    return "Object: " + QString::number(this->my_id);
}


//friend

bool operator==(const Object &o1, const Object &o2){
    //qDebug("equal check...");
    //return o1.my_id == o2.my_id;
    return o1.equal(o2);
}
