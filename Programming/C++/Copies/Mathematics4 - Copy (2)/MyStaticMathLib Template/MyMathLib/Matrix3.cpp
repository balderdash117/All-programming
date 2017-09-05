#include "Vector2.h"
#include "Vector3.h"
#include "Matrix3.h"

#include <memory.h>
#include <math.h>


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
	return  Matrix3(1.0f, 0.0f, 0.0f,0.0f, 1.0f, 0.0f,0.0f, 0.0f, 1.0f);

}

Matrix3 Matrix3::createTranslation(float a_x, float a_y, float a_z)
{
	return Matrix3(1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, a_x, a_y, a_z);
}

Matrix3 Matrix3::createTranslation(const Vector3 &a_vec)
{
	return Matrix3(1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, a_vec.x, a_vec.y, a_vec.z);
}

Matrix3 Matrix3::createTranslation(const Vector2 &a_vec, float a_z)
{
	return Matrix3(1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, a_vec.x, a_vec.y, a_z);
}

Matrix3 Matrix3::createRotation(float a_rot)
{
	return Matrix3(cosf(a_rot), sinf(a_rot), 0.0f, -sinf(a_rot), cosf(a_rot), 0.0f, 0.0f, 0.0f,1.0f);
}
Matrix3 Matrix3::createScale(float a_xScale, float a_yScale)
{
	return Matrix3(a_xScale, 0.0f, 0.0f, 0.0f, a_yScale, 1.0f, 0.0f, 0.0f, 0.0f);
}

Vector3 Matrix3::operator * (const Vector3 &a_vec) const
{
	return Vector3(
		v[0].x * a_vec.x + v[1].x * a_vec.y + v[2].x * a_vec.z,
		v[0].y * a_vec.x + v[1].y * a_vec.y + v[2].y * a_vec.z,
		v[0].z * a_vec.x + v[1].z * a_vec.y + v[2].z * a_vec.z);
}


Vector2 Matrix3::operator * (const Vector2 &a_vec) const
{
	return Vector2(
		v[0].x * a_vec.x + v[1].x * a_vec.y,
		v[0].y * a_vec.x + v[1].y * a_vec.y);
}

Matrix3  Matrix3::operator *(const Matrix3 &a_rhs) const
{
	return Matrix3(m1 * a_rhs.m1 + m2 * a_rhs.m4 + m3 * a_rhs.m7, m1 * a_rhs.m2 + m2 * a_rhs.m5 + m3 * a_rhs.m8, m1 * a_rhs.m3 + m2 * a_rhs.m6 + m3 * a_rhs.m9,
				   m4 * a_rhs.m1 + m5 * a_rhs.m4 + m6 * a_rhs.m7, m4 * a_rhs.m2 + m5 * a_rhs.m5 + m6 * a_rhs.m8, m4 * a_rhs.m3 + m5 * a_rhs.m6 + m6 * a_rhs.m9,
				   m7 * a_rhs.m1 + m8 * a_rhs.m4 + m9 * a_rhs.m7, m7 * a_rhs.m2 + m8 * a_rhs.m5 + m9 * a_rhs.m8, m7 * a_rhs.m3 + m8 * a_rhs.m6 + m9 * a_rhs.m9);
}

Matrix3 &Matrix3::operator *=(const Matrix3 &a_rhs) const
{
	Matrix3 t = *this * a_rhs;
	return t;
}

void  Matrix3::set(float a_m1, float a_m2, float a_m3,
	float a_m4, float a_m5, float a_m6,
	float a_m7, float a_m8, float a_m9)
{
}

void  Matrix3::set(float *a_ptr)
{
	memcpy(m, &a_ptr, sizeof(float) * 9);
}

// only set the translation component of the matrix
void Matrix3::setTranslation(float a_x, float a_y)
{
	m8 = a_x;
	m9 = a_y;
}

// only set the translation component of the matrix
void Matrix3::setTranslation(const Vector2 &a_vec)
{
	m8 = a_vec.x;
	m9 = a_vec.y;
}

void Matrix3::setRotateX(float a_rot)
{
		1.0f, 0.0f, 0.0f,
		0.0f, (cosf(a_rot), -sinf(a_rot)),
		0.0f, (sinf(a_rot), cosf(a_rot));
}

void Matrix3::setRotateY(float a_rot)
{
		(cosf(a_rot)), 0.0f, (sinf(a_rot)),
		0.0f, 1.0f, 0.0f,
		(-sinf(a_rot)), 0.0f, (cos(a_rot));

}

void Matrix3::setRotateZ(float a_rot)
{
		(cos(a_rot), -sinf(a_rot)), 0.0f,
		(sinf(a_rot), cosf(a_rot)), 0.0f,
		0.0f, 0.0f, 1.0f;

}
#if 0
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