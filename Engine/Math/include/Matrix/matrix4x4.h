#ifndef MATRIX4X4_H
#define MATRIX4X4_H

#include <QDebug>

#include "mathematics.h"
#include "mathematics_global.h"


class Matrix3x3;
class Vector4;
class Vector3;

/*column-major notation for openGL use...
  but using in code row-major notation for indizes...

  following stuff is colomn-major notation


    Indizes
    |    0        4        8        12   |
    |                                    |
    |    1        5        9        13   |
    |                                    |
    |    2        6        10       14   |
    |                                    |
    |    3        7        11       15   |

    Translation
    |    1        0        0        X    |
    |                                    |
    |    0        1        0        Y    |
    |                                    |
    |    0        0        1        Z    |
    |                                    |
    |    0        0        0        1    |

    Scale
    |    SX       0        0        0    |
    |                                    |
    |    0        SY       0        0    |
    |                                    |
    |    0        0        SZ       0    |
    |                                    |
    |    0        0        0        1    |

    Rotation X
    |    1        0        0        0    |
    |                                    |
    |    0      cos(?)   sin(?)     0    |
    |                                    |
    |    0     -sin(?)   cos(?)     0    |
    |                                    |
    |    0        0        0        1    |

    Rotation Y
    |  cos(?)     0    -sin(?)      0    |
    |                                    |
    |    0        1        0        0    |
    |                                    |
    |  sin(?)     0     cos(?)      0    |
    |                                    |
    |    0        0        0        1    |

    Rotation Z
    |  cos(?)  -sin(?)     0        0    |
    |                                    |
    |  sin(?)   cos(?)     0        0    |
    |                                    |
    |    0        0        1        0    |
    |                                    |
    |    0        0        0        1    |

    Directions
    |   RX        RY       RZ       12   |  R = right
    |                                    |
    |   UX        UY       UZ       13   |  U = up
    |                                    |
    |   LX        LY       LZ       14   |  L = look at (front)
    |                                    |
    |    3        7        11       15   |

*/

class MATHEMATICSSHARED_EXPORT Matrix4x4
{
public:

    //Multi-purpose constructors:
    Matrix4x4();
    Matrix4x4(double f1, double f2, double f3, double f4,
              double f5, double f6, double f7, double f8,
              double f9, double f10, double f11, double f12,
              double f13, double f14, double f15, double f16);
    Matrix4x4(const double *mat4);
    Matrix4x4(Matrix4x4 const& mat);



    void set_to_identity();
    bool is_identity();

    void translate(double x, double y, double z);
    void scale(double sx, double sy, double sz);

    void translate(Vector3 translate_vector);
    void scale(Vector3 scale_vector);

    void rotate_x(double degrees);
    void rotate_y(double degrees);
    void rotate_z(double degrees);

    void rotate(double angle, const Vector3 &vector);
    void rotate(double angle, double x, double y, double z);


    //Quaternion Class is missing...
    //void rotate(const Quaternion& quaternion);


    void pre_multiply(Matrix4x4 mat);
    void post_multiply(Matrix4x4 mat);



    double determinant() const;
    Matrix4x4 inverted(bool *invertible = 0) const;
    Matrix4x4 transposed() const;

    Matrix3x3 normalMatrix() const;

    void ortho(double left, double right, double bottom, double top, double nearPlane, double farPlane);
    void frustum(double left, double right, double bottom, double top, double nearPlane, double farPlane);
    void perspective(double angle, double aspect, double nearPlane, double farPlane);

    //Vector classes not done yet...
    //void lookAt(const Vector3& eye, const Vector3& center, const Vector3& up);

    Matrix3x3 rotationMatrix() const;

    void set_value(int index, double value);
    double get_value(int index);

    double* get_array();
    void set_array(double mat4[]);


    //Vector ops...
    Vector3 get_vector_up();
    Vector3 get_vector_right();
    Vector3 get_vector_look_at();

    Vector3 get_vector_pos();

    Vector3 get_vector_scale();


    //i hate inline but it's short...
    inline double *data(){
        // We have to assume that the caller will modify the matrix elements,
        // so we flip it over to "General" mode.
        flagBits = General;
        return mat4;
    }
    inline const double *data() const { return mat4; }
    inline const double *constData() const { return mat4; }



    void debug();

    //operators...
    MATHEMATICSSHARED_EXPORT const double& operator[](int index) const;
    MATHEMATICSSHARED_EXPORT double& operator[](int index);

    MATHEMATICSSHARED_EXPORT const double& operator()(int index) const;
    MATHEMATICSSHARED_EXPORT double& operator()(int index);

    MATHEMATICSSHARED_EXPORT const double& operator()(int row, int column) const;
    MATHEMATICSSHARED_EXPORT double& operator()(int row, int column);

    MATHEMATICSSHARED_EXPORT Matrix4x4& operator+=(const Matrix4x4& other);
    MATHEMATICSSHARED_EXPORT friend Matrix4x4 operator+(const Matrix4x4& m1, const Matrix4x4& m2);

    MATHEMATICSSHARED_EXPORT Matrix4x4& operator+=(const double& value);
    MATHEMATICSSHARED_EXPORT friend Matrix4x4 operator+(const Matrix4x4& m1, const double& value);
    MATHEMATICSSHARED_EXPORT friend Matrix4x4 operator+(const double& value, const Matrix4x4& m1);

    MATHEMATICSSHARED_EXPORT Matrix4x4& operator-=(const Matrix4x4& other);
    MATHEMATICSSHARED_EXPORT friend Matrix4x4 operator-(const Matrix4x4& m1, const Matrix4x4& m2);

    MATHEMATICSSHARED_EXPORT Matrix4x4& operator*=(const Matrix4x4& other);
    MATHEMATICSSHARED_EXPORT friend Matrix4x4 operator*(const Matrix4x4& m1, const Matrix4x4& m2);

    MATHEMATICSSHARED_EXPORT Matrix4x4& operator*=(const double& multiplier);
    MATHEMATICSSHARED_EXPORT friend Matrix4x4 operator*(const Matrix4x4& m1, const double& multiplier);
    MATHEMATICSSHARED_EXPORT friend Matrix4x4 operator*(const double& multiplier, const Matrix4x4& m1);

    MATHEMATICSSHARED_EXPORT Matrix4x4& operator/=(const double& divisor);
    MATHEMATICSSHARED_EXPORT friend Matrix4x4 operator/(const Matrix4x4& m1, const double& divisor);


    //Vector stuff
    MATHEMATICSSHARED_EXPORT friend Vector4 operator*(const Vector4& vector, const Matrix4x4& matrix);
    MATHEMATICSSHARED_EXPORT friend Vector4 operator*(const Matrix4x4& matrix, const Vector4& vector);

    MATHEMATICSSHARED_EXPORT friend Vector3 operator*(const Vector3& vector, const Matrix4x4& matrix);
    MATHEMATICSSHARED_EXPORT friend Vector3 operator*(const Matrix4x4& matrix, const Vector3& vector);

private:
    double mat4[16];

    int flagBits;           // Flag bits from the enum below.

    enum {
        Identity        = 0x0001,   // Identity matrix
        General         = 0x0002,   // General matrix, unknown contents
        Translation     = 0x0004,   // Contains a simple translation
        Scale           = 0x0008,   // Contains a simple scale
        Rotation        = 0x0010    // Contains a simple rotation
    };

    Matrix4x4 orthonormalInverse() const;

    //dirty inline hack ... i don't like it but its short :D
    Matrix4x4(int) { flagBits = General; }

};

#endif // MATRIX4X4_H
