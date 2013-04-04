#ifndef VECTOR3_H
#define VECTOR3_H


#include <math.h>
#include "matrix4.h"


struct vector3f
{
	float x, y, z;

	vector3f() { x=0.0f; y=0.0f; z=0.0f; }
	vector3f(const float _x, const float _y, const float _z) { x=_x; y=_y; z=_z; }

	void set(const float _x, const float _y, const float _z) { x=_x; y=_y; z=_z; }

    void reset() { x=0.0f; y=0.0f; z=0.0f; }

	const vector3f & operator = (const vector3f &v)
	{
		x = v.x; y = v.y; z = v.z;
		return *this;
	}

	//
	//vector -> vector operations
	//

	const vector3f operator + (const vector3f &v) const
	{
		return vector3f(x+v.x, y+v.y, z+v.z);
	}

	const vector3f operator - (const vector3f &v) const
	{
		return vector3f(x - v.x, y - v.y, z - v.z);
	}

	const vector3f & operator += (const vector3f &v)
	{
		x += v.x; y += v.y; z += v.z;
		return *this;
	}

	const vector3f & operator -= (const vector3f &v)
	{
		x -= v.x; y -= v.y; z -= v.z;
		return *this;
	}

	const vector3f & operator *= (const vector3f &v)
	{
		x *= v.x; y *= v.y; z *= v.z;
		return *this;
	}

	const vector3f & operator /= (const vector3f &v)
	{
		x /= v.x; y /= v.y; z /= v.z;
		return *this;
	}


	//
	//vector -> scalar operations
	//

	const vector3f operator * (const float &s) const
	{
		return vector3f(x * s, y * s, z * s);
	}

	const vector3f operator / (const float &s) const
	{
		return vector3f(x / s, y / s, z / s);
	}

	const vector3f & operator *= (const float s)
	{
		x *= s; y *= s; z *= s;
		return *this;
	}

	const vector3f & operator /= (const float s)
	{
		x /= s; y /= s; z /= s;
		return *this;
	}

	float length() const
	{
		return sqrtf(x*x + y*y + z*z);
	}


	//
	//modifiers
	//

	void normalize()
	{
		*this /= length();
	}

	vector3f normalized() const
	{
		return (*this / length());
	}

	bool isNull() const
	{
		if (x == 0 && y == 0 && z == 0)
			return true;
		return false;
	}

	inline float* getPtr() { return &x; }

	inline const float* getConstPtr() const { return &x; }

	//
	//matrix operations
	//

    vector3f operator * (const matrix4f& m) const
	{
		return vector3f(
			x*m.m11 + y*m.m21 + z*m.m31,
			x*m.m12 + y*m.m22 + z*m.m32,
			x*m.m13 + y*m.m23 + z*m.m33);
	}

    const vector3f & operator *= (const matrix4f& m)
	{
	    x = x*m.m11 + y*m.m21 + z*m.m31;
	    y = x*m.m12 + y*m.m22 + z*m.m32;
        z = x*m.m13 + y*m.m23 + z*m.m33;
        return *this;
	}
};


#endif // VECTOR3_H
