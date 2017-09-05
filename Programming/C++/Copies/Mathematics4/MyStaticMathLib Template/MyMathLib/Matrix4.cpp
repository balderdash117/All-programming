#include "Matrix4.h"

#include <memory.h>
#include <math.h>
#if 0
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
}

Matrix4  Matrix4::operator *(const Matrix4 &a_rhs) const
{
}


void Matrix4::setRotateX(float a_rot)
{
}

void Matrix4::setRotateY(float a_rot)
{
}

void Matrix4::setRotateZ(float a_rot)
{
}
#endif 0