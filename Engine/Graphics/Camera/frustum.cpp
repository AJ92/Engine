#include "frustum.h"

Frustum::Frustum() :
    Component()
{
}

Frustum::~Frustum(){
    //qDebug("Frustum::~Frustum");
}

void Frustum::setCamInt(double angle, double ratio, double z_near, double z_far){
    // store the information
    this->ratio = ratio;
    this->angle = angle;
    this->z_near = z_near;
    this->z_far = z_far;

    // compute width and height of the near and far plane sections
    tang = (float)tan(ANG2RAD * angle * 0.5) ;
    nh = z_near * tang;
    nw = nh * ratio;
    fh = z_far  * tang;
    fw = fh * ratio;
}

void Frustum::setCamDef(Vector3 pos, Vector3 lookat, Vector3 up){

    Vector3 dir,nc,fc,X,Y,Z;

    // compute the Z axis of camera
    // this axis points in the opposite direction from
    // the looking direction
    Z = pos - lookat;
    Z.normalize();

    // X axis of camera with given "up" vector and Z axis
    X = Vector3::crossProduct(up,Z);
    X.normalize();

    // the real "up" vector is the cross product of Z and X
    Y = Vector3::crossProduct(Z,X);

    // compute the centers of the near and far planes
    nc = pos - (Z * z_near);
    fc = pos - (Z * z_far);

    ntl = nc + Y * nh - X * nw;
    ntr = nc + Y * nh + X * nw;
    nbl = nc - Y * nh - X * nw;
    nbr = nc - Y * nh + X * nw;

    ftl = fc + Y * fh - X * fw;
    ftr = fc + Y * fh + X * fw;
    fbl = fc - Y * fh - X * fw;
    fbr = fc - Y * fh + X * fw;

    points[0] = ntl;
    points[1] = ntr;
    points[2] = nbl;
    points[3] = nbr;

    points[4] = ftl;
    points[5] = ftr;
    points[6] = fbl;
    points[7] = fbr;

    /*
    //debug
    qDebug() << "nearplane";
    qDebug() << ntl[0];
    qDebug() << ntl[1];
    qDebug() << ntl[2];

    qDebug() << " ";
    qDebug() << ntr[0];
    qDebug() << ntr[1];
    qDebug() << ntr[2];

    qDebug() << " ";
    qDebug() << nbl[0];
    qDebug() << nbl[1];
    qDebug() << nbl[2];

    qDebug() << " ";
    qDebug() << nbr[0];
    qDebug() << nbr[1];
    qDebug() << nbr[2];

    qDebug() << "farplane";
    qDebug() << ftl[0];
    qDebug() << ftl[1];
    qDebug() << ftl[2];

    qDebug() << " ";
    qDebug() << ftr[0];
    qDebug() << ftr[1];
    qDebug() << ftr[2];

    qDebug() << " ";
    qDebug() << fbl[0];
    qDebug() << fbl[1];
    qDebug() << fbl[2];

    qDebug() << " ";
    qDebug() << nbr[0];
    qDebug() << nbr[1];
    qDebug() << nbr[2];
    */

    planes[TOP]= Plane(ntr,ntl,ftl);
    planes[BOTTOM]= Plane(nbl,nbr,fbr);
    planes[LEFT]= Plane(ntl,nbl,fbl);
    planes[RIGHT]= Plane(nbr,ntr,fbr);
    planes[NEARp]= Plane(ntl,ntr,nbr);
    planes[FARp]= Plane(ftr,ftl,fbl);
}

void Frustum::setPoints(Vector3 ntl, Vector3 ntr, Vector3 nbl, Vector3 nbr,
               Vector3 ftl, Vector3 ftr, Vector3 fbl, Vector3 fbr){

    this->ntl = ntl;
    this->ntr = ntr;
    this->nbl = nbl;
    this->nbr = nbr;

    this->ftl = ftl;
    this->ftr = ftr;
    this->fbl = fbl;
    this->fbr = fbr;

    planes[TOP]= Plane(ntr,ntl,ftl);
    planes[BOTTOM]= Plane(nbl,nbr,fbr);
    planes[LEFT]= Plane(ntl,nbl,fbl);
    planes[RIGHT]= Plane(nbr,ntr,fbr);
    planes[NEARp]= Plane(ntl,ntr,nbr);
    planes[FARp]= Plane(ftr,ftl,fbl);
}

int Frustum::pointInFrustum(Vector3 pos){
    int result = Inside;

    for(int i=0; i < 6; i++) {
        if (planes[i].distance(pos) < 0)
            return Outside;
    }
    return(result);
}

int Frustum::sphereInFrustum(Vector3 pos, double radius){
    double distance;

    int result = Inside;

    for(int i=0; i < 6; i++) {
        distance = planes[i].distance(pos);

        //qDebug() << "distance";
        //qDebug() << distance;


        if (distance < -radius)
            return Outside;
        else if (distance < radius)
            result =  Intersect;
    }
    return(result);
}

Vector3 Frustum::get_ntl(){
    return ntl;
}

Vector3 Frustum::get_ntr(){
    return ntr;
}

Vector3 Frustum::get_nbl(){
    return nbl;
}

Vector3 Frustum::get_nbr(){
    return nbr;
}

Vector3 Frustum::get_ftl(){
    return ftl;
}

Vector3 Frustum::get_ftr(){
    return ftr;
}

Vector3 Frustum::get_fbl(){
    return fbl;
}

Vector3 Frustum::get_fbr(){
    return fbr;
}
