#ifndef OBJECT_H
#define OBJECT_H

#include <QString>

#include <vector>

/*
  Using unsigned long long: 0 to 18446744073709551615
  */

class Object
{

public:
    Object();
    ~Object();

    unsigned long long id() const;

    //equivalent to java language...
    virtual bool equal(const Object &obj) const;
    virtual QString to_string();

    friend bool operator==(const Object &o1, const Object &o2);

private:
    static unsigned long long static_id;

    //stores freed IDs for reuse...
    static std::vector<unsigned long long> unused_ids;

    static unsigned long long next_id();
    unsigned long long my_id;

};

#endif // OBJECT_H
