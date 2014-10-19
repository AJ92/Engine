#ifndef VECTOR4_H
#define VECTOR4_H

#include <QDebug>
#include "mathematics.h"
#include "mathematics_global.h"

/*

  Indizes
  |     0       1       2       3       |

  Pos
  |     x       y       z       w       |

*/
class Matrix4x4;

class MATHEMATICSSHARED_EXPORT Vector4
{
public:
    Vector4();
    Vector4(double f);
    Vector4(double x, double y, double z, double w);
    Vector4(const double *vec4);
    Vector4(Vector4 const& vec);

    void set_to_null();

    bool is_null() const;

    void set_value(int index, double value);
    double get_value(int index);

    double x() const;
    double y() const;
    double z() const;
    double w() const;

    void set_x(double x);
    void set_y(double y);
    void set_z(double z);
    void set_w(double w);



    double length() const;
    double lengthSquared() const;

    Vector4 normalized() const;
    void normalize();





    //operators...
    MATHEMATICSSHARED_EXPORT const double& operator[](int index) const;
    MATHEMATICSSHARED_EXPORT double& operator[](int index);

    MATHEMATICSSHARED_EXPORT const double& operator()(int index) const;
    MATHEMATICSSHARED_EXPORT double& operator()(int index);


    MATHEMATICSSHARED_EXPORT Vector4 &operator+=(const Vector4 &vector);
    MATHEMATICSSHARED_EXPORT Vector4 &operator-=(const Vector4 &vector);
    MATHEMATICSSHARED_EXPORT Vector4 &operator*=(double factor);
    MATHEMATICSSHARED_EXPORT Vector4 &operator*=(const Vector4 &vector);
    MATHEMATICSSHARED_EXPORT Vector4 &operator/=(double divisor);

    static double dotProduct(const Vector4& v1, const Vector4& v2);

    MATHEMATICSSHARED_EXPORT friend bool operator==(const Vector4 &v1, const Vector4 &v2);
    MATHEMATICSSHARED_EXPORT friend bool operator!=(const Vector4 &v1, const Vector4 &v2);
    MATHEMATICSSHARED_EXPORT friend const Vector4 operator+(const Vector4 &v1, const Vector4 &v2);
    MATHEMATICSSHARED_EXPORT friend const Vector4 operator-(const Vector4 &v1, const Vector4 &v2);
    MATHEMATICSSHARED_EXPORT friend const Vector4 operator*(double factor, const Vector4 &vector);
    MATHEMATICSSHARED_EXPORT friend const Vector4 operator*(const Vector4 &vector, double factor);
    MATHEMATICSSHARED_EXPORT friend const Vector4 operator*(const Vector4 &v1, const Vector4& v2);
    MATHEMATICSSHARED_EXPORT friend const Vector4 operator-(const Vector4 &vector);
    MATHEMATICSSHARED_EXPORT friend const Vector4 operator/(const Vector4 &vector, double divisor);


    //Matrix stuff
    MATHEMATICSSHARED_EXPORT friend Vector4 operator*(const Vector4& vector, const Matrix4x4& matrix);
    MATHEMATICSSHARED_EXPORT friend Vector4 operator*(const Matrix4x4& matrix, const Vector4& vector);


private:
    double vec4[4];

    //dirty inline hack ... i don't like it but its short :D
    Vector4(int) { }

};

#endif // VECTOR4_H
