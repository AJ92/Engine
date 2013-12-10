#ifndef OBJECT_H
#define OBJECT_H

#include <QString>

class Object
{

public:
    Object();

    long id();

    //equivalent to java language...
    virtual bool equal(Object obj);
    virtual QString to_string();


    friend bool operator==(const Object &o1, const Object &o2);


private:
    static long static_id;

    static long next_id();
    long my_id;

};

#endif // OBJECT_H
