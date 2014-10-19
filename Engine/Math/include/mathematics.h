#ifndef MATHEMATICS_H
#define MATHEMATICS_H


#include <cmath>

// Pre-calculated value of PI / 180.
#define kPI180   0.017453

// Pre-calculated value of 180 / PI.
#define k180PI  57.295780

// Converts degrees to radians.
#define degreesToRadians(x) (x * kPI180)

// Converts radians to degrees.
#define radiansToDegrees(x) (x * k180PI)


#ifndef MATHEMATICS_VECTOR_H
#define MATHEMATICS_VECTOR_H
#include "Vector/vector3.h"
#include "Vector/vector4.h"
#endif // MATHEMATICS_VECTOR_H

#ifndef MATHEMATICS_MATRIX_H
#define MATHEMATICS_MATRIX_H
#include "Matrix/matrix3x3.h"
#include "Matrix/matrix4x4.h"
#endif // MATHEMATICS_MATRIX_H



#endif // MATHEMATICS_H
