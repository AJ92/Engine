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


private:
    static long static_id;

    static long next_id();
    const long my_id;

};

#endif // OBJECT_H
