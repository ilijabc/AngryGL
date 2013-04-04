/*
	by Ilija
*/


#include "matrix4.h"
#include "quat.h"
#include "vector3.h"


matrix4f matrix4f::operator * (const matrix4f& other) const
{
	matrix4f result;
	for (int i = 0; i < 16; i += 4)
	{
		for (int j = 0; j < 4; j++)
		{
			result.setElement(
				getElement( i + 0) * other.getElement( 0 + j) + getElement( i + 1) * other.getElement( 4 + j) +
				getElement( i + 2) * other.getElement( 8 + j) + getElement( i + 3) * other.getElement(12 + j),
				i + j);
		}
	}
	return result;
}

const matrix4f& matrix4f::operator *= (const matrix4f& other)
{
	matrix4f result;
	for (int i = 0; i < 16; i += 4)
	{
		for (int j = 0; j < 4; j++)
		{
			result.setElement(
				getElement( i + 0) * other.getElement( 0 + j) + getElement( i + 1) * other.getElement( 4 + j) +
				getElement( i + 2) * other.getElement( 8 + j) + getElement( i + 3) * other.getElement(12 + j),
				i + j);
		}
	}
	return *this = result;
}


void matrix4f::rotate(float t, const vector3f& axis)
{
	quatf q(t, axis);
	*this = *this * q.getMatrix();
}

