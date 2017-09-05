#include "Vector2.h"
#include "Vector3.h"
#include "Matrix3.h"

#include <memory.h>
#include <math.h>

#if 0
Matrix3 & Matrix3::operator=(const Matrix3 & a_rhs)
{
	return *this;
}

Matrix3::Matrix3()
{
}

Matrix3::Matrix3(float *a_ptr) :
	m1(a_ptr[0]), m2(a_ptr[1]), m3(a_ptr[2]),
	m4(a_ptr[3]), m5(a_ptr[4]), m6(a_ptr[5]),
	m7(a_ptr[6]), m8(a_ptr[7]), m9(a_ptr[8])
{
}

Matrix3::Matrix3(float a_m1, float a_m2, float a_m3, float a_m4, float a_m5, float a_m6, float a_m7, float a_m8, float a_m9) :
	m1(a_m1), m2(a_m2), m3(a_m3),
	m4(a_m4), m5(a_m5), m6(a_m6),
	m7(a_m7), m8(a_m8), m9(a_m9)
{
}

Matrix3 Matrix3::createIdentity()
{
}

Matrix3 Matrix3::createTranslation(float a_x, float a_y, float a_z)
{
}

Matrix3 Matrix3::createTranslation(const Vector3 &a_vec)
{
}

Matrix3 Matrix3::createTranslation(const Vector2 &a_vec, float a_z)
{
}

Matrix3 Matrix3::createRotation(float a_rot)
{
	return Matrix3(cosf(a_rot), sinf(a_rot), 0.0f, -sinf(a_rot), cosf(a_rot), 0.0f, 0.0f, 0.0f 1.0f);
}
Matrix3 Matrix3::createScale(float a_xScale, float a_yScale)
{
}

Vector3 Matrix3::operator * (const Vector3 &a_vec) const
{
}


Vector2 Matrix3::operator * (const Vector2 &a_vec) const
{
}

Matrix3  Matrix3::operator *(const Matrix3 &a_rhs) const
{
}

Matrix3 &Matrix3::operator *=(const Matrix3 &a_rhs) const
{
}

void  Matrix3::set(float a_m1, float a_m2, float a_m3,
	float a_m4, float a_m5, float a_m6,
	float a_m7, float a_m8, float a_m9)
{
}

void  Matrix3::set(float *a_ptr)
{
}

// only set the translation component of the matrix
void Matrix3::setTranslation(float a_x, float a_y)
{
}

// only set the translation component of the matrix
void Matrix3::setTranslation(const Vector2 &a_vec)
{
}

void Matrix3::setRotateX(float a_rot)
{
}

void Matrix3::setRotateY(float a_rot)
{
}

void Matrix3::setRotateZ(float a_rot)
{
}

float Matrix3::getRotationZ()
{
}

// add x and y onto the translation component of the matrix
void Matrix3::translate(float a_x, float a_y)
{
}

// add x and y onto the translation component of the matrix
void Matrix3::translate(const Vector2 &a_vec)
{
}

// returns the translation component of the matrix
Vector2 Matrix3::getTranslation() const
{
}

#endif 0