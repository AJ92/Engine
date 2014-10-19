#ifndef PLANE_H
#define PLANE_H

#include "mathematics.h"

#include "mathematics_global.h"

/*

    Ax + By + Cz + D = 0

Assuming three points p0, p1, and p2 the coefficients A, B, C and D can be computed as follows:

    Compute vectors v = p1 – p0, and u = p2 – p0;
    Compute n = v x u (cross product)
    Normalize n
    Assuming n = (xn,yn,zn) is the normalized normal vector then
        A = xn
        B = yn
        C = zn
    To compute the value of D we just use the equation above,
    hence -D = Ax + By + Cz. Replacing (x,y,z) for a point in the plane (for instance p0),
    we get D = – n . p0 (dot product).


Distance from a point to a plane:

    Assuming that the equation Ax + By + Cz + D = 0 has been obtained as shown above
    then the distance from the plane to a point r(rx,ry,rz) can be obtained
    just by computing the left side of equation, or

        dist = A*rx + B*ry + C*rz + D = n . r  + D

    Actually the distance is the absolute value of dist, but the sign of dist
    (if it is zero is on the plane) also gives information as to which side of the plane
    is point r. If the sign is positive then the point is on the side that agrees with
    the normal n, otherwise it is on the other side.


Projecting a point to a plane

    The projection of a point q on a plane defined by Ax + By + Cz + D = 0 is the
    point on the plane that is closest to q.

    Assume that dist is the signed distance from q to the plane.
    Then the closest point p on the plane is:

        p = q - dist * n


Credits to: http://www.lighthouse3d.com
*/

class MATHEMATICSSHARED_EXPORT Plane
{
public:
    //dummy constructor
    Plane();
    //create the plane from 3 points
    Plane(Vector3 point1, Vector3 point2, Vector3 point3);
    //or form a point and a normal
    Plane(Vector3 point, Vector3 normal);

    double distance(Vector3 toPoint);
    Vector3 project(Vector3 fromPoint);

private:
    Vector3 plane_point;
    Vector3 plane_normal;
    double d;


};

#endif // PLANE_H
