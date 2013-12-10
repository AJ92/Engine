#include "object.h"


//init the next_id var...
long Object::static_id = 0;

/*!
  Constructs an Object with an unique identifier.
  */
Object::Object():
    my_id(next_id())
{

}

/*!
  Returns the identifier that was constructed during object creation.
  */
long Object::id(){
    return my_id;
}

/*!
  "Generates" the identifier. Is used during construction.

  \sa Object()
  */
long Object::next_id(){
    static_id++;
    return static_id;
}

/*!
  Checks if the \a obj is equals itself.

  Can be overloaded...
  */
bool Object::equal(Object obj){
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
    return o1.my_id == o2.my_id;
}

