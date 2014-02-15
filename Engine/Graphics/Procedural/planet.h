#ifndef PLANET_H
#define PLANET_H

#include "Object/object.h"
#include "planetlod.h"

class Planet : public Object
{
public:
    Planet(int random_seed);

private:
    int seed;

    void createLod();
};

#endif // PLANET_H
