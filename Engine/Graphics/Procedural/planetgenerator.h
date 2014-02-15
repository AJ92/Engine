#ifndef PLANETGENERATOR_H
#define PLANETGENERATOR_H

#include "planet.h"
#include <QVector>
#include "mathematics.h"

class PlanetGenerator
{
public:
    PlanetGenerator();

    Planet * generatePlanet(int random_seed);
};

#endif // PLANETGENERATOR_H
