#ifndef AABB_H
#define AABB_H

#include "mathematics.h"

#include "mathematics_global.h"

class MATHEMATICSSHARED_EXPORT AABB
{
public:
    AABB();
    AABB(Vector3 bmin, Vector3 bmax);
    AABB(double bmin_x, double bmin_y, double bmin_z,
         double bmax_x, double bmax_y, double bmax_z);


    Vector3 getBmin();
    Vector3 getBmax();

    void setBmin(Vector3 bmin);
    void setBmax(Vector3 bmax);

    void setBmin(double bmin_x, double bmin_y, double bmin_z);
    void setBmax(double bmax_x, double bmax_y, double bmax_z);

private:
    Vector3 bmin;
    Vector3 bmax;
};

#endif // AABB_H
