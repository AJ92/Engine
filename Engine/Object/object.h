#ifndef OBJECT_H
#define OBJECT_H

#include <QString>



/*
  Using unsigned long long: 0 to 18446744073709551615



  */

class Object
{

public:
    Object();

    unsigned long long id();

    //equivalent to java language...
    virtual bool equal(Object obj);
    virtual QString to_string();


    friend bool operator==(const Object &o1, const Object &o2);


private:
    static unsigned long long static_id;


    static unsigned long long next_id();
    unsigned long long my_id;

};

#endif // OBJECT_H
