#ifndef FRUSTUM_H
#define FRUSTUM_H

#include "Object/object.h"
#include "Math/mathematics.h"
#include "Math/Geometry/plane.h"

//PI / 180 degree (very good, much precise, such math)
#define ANG2RAD 3.14159265358979323846/180.0

class Frustum : public Object
{
public:
    Frustum();
    ~Frustum();

    enum IntersectionType {
        Inside      = 0x0000,
        Outside     = 0x0001,
        Intersect   = 0x0002
    };

    void setCamInt(double angle, double ratio, double z_near, double z_far);
    void setCamDef(Vector3 pos, Vector3 lookat, Vector3 up);
    void setPoints(Vector3 ntl, Vector3 ntr, Vector3 nbl, Vector3 nbr,
                   Vector3 ftl, Vector3 ftr, Vector3 fbl, Vector3 fbr);

    int pointInFrustum(Vector3 pos);
    int sphereInFrustum(Vector3 pos, double radius);

    //debug stuff
    Vector3 get_ntl();
    Vector3 get_ntr();
    Vector3 get_nbl();
    Vector3 get_nbr();
    Vector3 get_ftl();
    Vector3 get_ftr();
    Vector3 get_fbl();
    Vector3 get_fbr();

private:
    //n: near
    //f: far
    //t: top
    //b: bottom
    //r: right
    //l: left
    //w: width
    //h: height
    Vector3 ntl,ntr,nbl,nbr,ftl,ftr,fbl,fbr;
    double z_near, z_far, ratio, angle, tang;
    double nw,nh,fw,fh;


    enum PlaneSide{
        TOP = 0,
        BOTTOM = 1,
        LEFT = 2,
        RIGHT = 3,
        NEARp = 4,
        FARp = 5
    };

    Plane planes[6];
    Vector3 points[8];
};

#endif // FRUSTUM_H
