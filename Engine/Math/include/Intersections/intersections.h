#ifndef INTERSECTIONS_H
#define INTERSECTIONS_H

#include "Geometry/aabb.h"
#include "Geometry/sphere.h"

#include "mathematics_global.h"


class MATHEMATICSSHARED_EXPORT Intersections
{
public:
    Intersections();

    static double square(double a);
    static bool sphereAABBIntersection(Sphere s, AABB a);
    static bool pointInAABB(Vector3 point , AABB a);
    static bool pointInSphere(Vector3 point , Sphere s);

};

#endif // INTERSECTIONS_H
