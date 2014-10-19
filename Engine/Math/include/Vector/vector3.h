#ifndef VECTOR3_H
#define VECTOR3_H

#include <QDebug>
#include "mathematics.h"
#include "mathematics_global.h"


/*

  Indizes
  |     0       1       2        |

  Pos
  |     x       y       z        |

*/


class Matrix4x4;

class MATHEMATICSSHARED_EXPORT Vector3
{
public:
    Vector3();
    Vector3(double f);
    Vector3(double x, double y, double z);
    Vector3(const double *vec3);
    Vector3(Vector3 const& vec);

    void set_to_null();

    bool is_null() const;

    void set_value(int index, double value);
    double get_value(int index);

    double x() const;
    double y() const;
    double z() const;


    void set_x(double x);
    void set_y(double y);
    void set_z(double z);




    double length() const;
    double lengthSquared() const;

    Vector3 normalized() const;
    void normalize();


    double distance(Vector3 vector);



    //operators...
    const double& operator[](int index) const;
    double& operator[](int index);

    const double& operator()(int index) const;
    double& operator()(int index);


    MATHEMATICSSHARED_EXPORT Vector3 &operator+=(const Vector3 &vector);
    MATHEMATICSSHARED_EXPORT Vector3 &operator-=(const Vector3 &vector);
    MATHEMATICSSHARED_EXPORT Vector3 &operator*=(double factor);
    MATHEMATICSSHARED_EXPORT Vector3 &operator*=(const Vector3 &vector);
    MATHEMATICSSHARED_EXPORT Vector3 &operator/=(double divisor);

    static double dotProduct(const Vector3& v1, const Vector3& v2);
    static Vector3 crossProduct(const Vector3& v1, const Vector3& v2);
    static Vector3 normal(const Vector3& v1, const Vector3& v2);
    static Vector3 normal(const Vector3& v1, const Vector3& v2, const Vector3& v3);


    MATHEMATICSSHARED_EXPORT friend bool operator==(const Vector3 &v1, const Vector3 &v2);
    MATHEMATICSSHARED_EXPORT friend bool operator!=(const Vector3 &v1, const Vector3 &v2);
    MATHEMATICSSHARED_EXPORT friend const Vector3 operator+(const Vector3 &v1, const Vector3 &v2);
    MATHEMATICSSHARED_EXPORT friend const Vector3 operator-(const Vector3 &v1, const Vector3 &v2);
    MATHEMATICSSHARED_EXPORT friend const Vector3 operator*(double factor, const Vector3 &vector);
    MATHEMATICSSHARED_EXPORT friend const Vector3 operator*(const Vector3 &vector, double factor);
    MATHEMATICSSHARED_EXPORT friend const Vector3 operator*(const Vector3 &v1, const Vector3& v2);
    MATHEMATICSSHARED_EXPORT friend const Vector3 operator-(const Vector3 &vector);
    MATHEMATICSSHARED_EXPORT friend const Vector3 operator/(const Vector3 &vector, double divisor);


    //Matrix stuff
    MATHEMATICSSHARED_EXPORT friend Vector3 operator*(const Vector3& vector, const Matrix4x4& matrix);
    MATHEMATICSSHARED_EXPORT friend Vector3 operator*(const Matrix4x4& matrix, const Vector3& vector);


private:
    double vec3[3];

    //dirty inline hack ... i don't like it but its short :D
    Vector3(int) { }
};

#endif // VECTOR3_H
