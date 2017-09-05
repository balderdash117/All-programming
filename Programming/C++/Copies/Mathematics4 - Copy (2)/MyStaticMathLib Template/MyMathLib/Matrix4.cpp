#include "Matrix4.h"

#include <memory.h>
#include <math.h>

Matrix4::~Matrix4()
{
}

Matrix4::Matrix4()
{
}

void  Matrix4::set(float *a_ptr)
{
}

void  Matrix4::set(float a_m1, float a_m2, float a_m3, float a_m4, 
	float a_m5, float a_m6, float a_m7, float a_m8, 
	float a_m9, float a_m10, float a_m11, float a_m12,
	float a_m13, float a_m14, float a_m15, float a_m16)
{
	m1 = a_m1; m2 = a_m2; m3 = a_m3; m4 = a_m4; 
	m5 = a_m5; m6 = a_m6; m7 = a_m7; m8 = a_m8; 
	m9 = a_m9; m10 = a_m10; m11 = a_m11; m12 = a_m12;
	m13 = a_m13; m14 = a_m14; m15 = a_m15; m16 = a_m16;
}


Matrix4::Matrix4(float *a_ptr) :
	m1(a_ptr[0]), m2(a_ptr[1]), m3(a_ptr[2]),
	m4(a_ptr[3]), m5(a_ptr[4]), m6(a_ptr[5]),
	m7(a_ptr[6]), m8(a_ptr[7]), m9(a_ptr[8])
{
}

Matrix4::Matrix4(float a_m1, float a_m2, float a_m3, float a_m4, float a_m5, float a_m6, float a_m7, float a_m8, float a_m9, float a_m10, float a_m11, float a_m12,
	float a_m13, float a_m14, float a_m15, float a_m16) :
	m1 ( a_m1), m2 (a_m2),  m3 (a_m3),  m4 (a_m4), 
	m5 ( a_m5), m6 (a_m6),  m7 (a_m7),  m8 (a_m8), 
	m9 ( a_m9), m10(a_m10), m11(a_m11), m12(a_m12),
	m13(a_m13), m14(a_m14), m15(a_m15), m16(a_m16)
{
}

Vector4 Matrix4::operator * (const Vector4 &a_vec) const
{
	return Vector4(
		v[0].x * a_vec.x + v[1].x * a_vec.y + v[2].x * a_vec.z + v[3].x * a_vec.w,
		v[0].y * a_vec.x + v[1].y * a_vec.y + v[2].y * a_vec.z + v[3].y * a_vec.w,
		v[0].z * a_vec.x + v[1].z * a_vec.y + v[2].z * a_vec.z + v[3].z * a_vec.w,
		v[0].w * a_vec.x + v[1].w * a_vec.y + v[2].w * a_vec.z + v[3].w * a_vec.w);
}


Matrix4  Matrix4::operator *(const Matrix4 &a_rhs) const
{
	return Matrix4(m1 * a_rhs.m1 + m2 * a_rhs.m5 + m3 * a_rhs.m9 + m4* a_rhs.m13, m1 * a_rhs.m2 + m2 * a_rhs.m6 + m3 * a_rhs.m10 + m4 * a_rhs.m14,
				   m1 * a_rhs.m3 + m2 * a_rhs.m7 + m3 * a_rhs.m11 + m4 * a_rhs.m15, m1 * a_rhs.m4 + m2 * a_rhs.m8 + m3 * a_rhs.m12 + m4 * a_rhs.m16,
				   m5 * a_rhs.m1 + m6 * a_rhs.m5 + m7 * a_rhs.m9 + m8* a_rhs.m13, m5 * a_rhs.m2 + m6 * a_rhs.m6 + m7 * a_rhs.m10 + m8 * a_rhs.m14,
		           m5 * a_rhs.m3 + m6 * a_rhs.m7 + m7 * a_rhs.m11 + m8 * a_rhs.m15, m5 * a_rhs.m4 + m6 * a_rhs.m8 + m7 * a_rhs.m12 + m8 * a_rhs.m16,
				   m9 * a_rhs.m1 + m10 * a_rhs.m5 + m11 * a_rhs.m9 + m12* a_rhs.m13, m9 * a_rhs.m2 + m10 * a_rhs.m6 + m11 * a_rhs.m10 + m12 * a_rhs.m14,
		           m9 * a_rhs.m3 + m10 * a_rhs.m7 + m11 * a_rhs.m11 + m12 * a_rhs.m15, m9 * a_rhs.m4 + m10 * a_rhs.m8 + m11 * a_rhs.m12 + m12 * a_rhs.m16,
				   m13 * a_rhs.m1 + m14 * a_rhs.m5 + m15 * a_rhs.m9 + m16* a_rhs.m13, m13 * a_rhs.m2 + m14 * a_rhs.m6 + m15 * a_rhs.m10 + m16 * a_rhs.m14,
		           m13 * a_rhs.m3 + m14 * a_rhs.m7 + m15 * a_rhs.m11 + m16 * a_rhs.m15, m13 * a_rhs.m4 + m14 * a_rhs.m8 + m15 * a_rhs.m12 + m16 * a_rhs.m16);
}


void Matrix4::setRotateX(float a_rot)
{
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, (cosf(a_rot), -sinf(a_rot)), 0.0f,
		0.0f, (sinf(a_rot), cosf(a_rot)), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f;
}

void Matrix4::setRotateY(float a_rot)
{
		(cosf(a_rot)), 0.0f, (sinf(a_rot)), 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		(-sinf(a_rot)), 0.0f, (cosf(a_rot)), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f;
}

void Matrix4::setRotateZ(float a_rot)
{
		(cosf(a_rot), -sinf(a_rot)), 0.0f, 0.0f,
		(sinf(a_rot), cosf(a_rot)), 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f;
}
