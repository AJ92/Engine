#ifndef MATRIX3X3_H
#define MATRIX3X3_H

#include <QDebug>

#include "Vector/vector3.h"
#include "Vector/vector4.h"
#include "Matrix/Matrix4x4.h"
#include "mathematics.h"

#include "mathematics_global.h"

/*column-major notation for openGL use...
  but using in code row-major notation for indizes...

  following stuff is colomn-major notation


    Indizes
    |    0        3        6    |
    |                           |
    |    1        4        7    |
    |                           |
    |    2        5        8    |

*/


class MATHEMATICSSHARED_EXPORT Matrix3x3
{
public:
    //Multi-purpose constructors:
    Matrix3x3();
    Matrix3x3(double f1, double f2, double f3,
              double f4, double f5, double f6,
              double f7, double f8, double f9);
    Matrix3x3(const double *mat3);
    Matrix3x3(Matrix3x3 const& mat);

    void set_to_identity();
    bool is_identity();



    void set_value(int index, double value);
    double get_value(int index);

    double* get_array();
    void set_array(double mat3[]);

    void debug();

    //operators...
    const double& operator[](int index) const;
    double& operator[](int index);

    const double& operator()(int index) const;
    double& operator()(int index);

    const double& operator()(int row, int column) const;
    double& operator()(int row, int column);

    Matrix3x3& operator+=(const Matrix3x3& other);
    friend Matrix3x3 operator+(const Matrix3x3& m1, const Matrix3x3& m2);

    Matrix3x3& operator+=(const double& value);
    friend Matrix3x3 operator+(const Matrix3x3& m1, const double& value);
    friend Matrix3x3 operator+(const double& value, const Matrix3x3& m1);

    Matrix3x3& operator-=(const Matrix3x3& other);
    friend Matrix3x3 operator-(const Matrix3x3& m1, const Matrix3x3& m2);

    Matrix3x3& operator*=(const Matrix3x3& other);
    friend Matrix3x3 operator*(const Matrix3x3& m1, const Matrix3x3& m2);

    Matrix3x3& operator*=(const double& multiplier);
    friend Matrix3x3 operator*(const Matrix3x3& m1, const double& multiplier);
    friend Matrix3x3 operator*(const double& multiplier, const Matrix3x3& m1);

    Matrix3x3& operator/=(const double& divisor);
    friend Matrix3x3 operator/(const Matrix3x3& m1, const double& divisor);

private:
    double mat3[9];

    int flagBits;           // Flag bits from the enum below.

    enum {
        Identity        = 0x0001,   // Identity matrix
        General         = 0x0002,   // General matrix, unknown contents
        Translation     = 0x0004,   // Contains a simple translation
        Scale           = 0x0008,   // Contains a simple scale
        Rotation        = 0x0010    // Contains a simple rotation
    };

    Matrix3x3(int) { flagBits = General; }
};

#endif // MATRIX3X3_H
