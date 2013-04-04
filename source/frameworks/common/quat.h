#ifndef QUAT_H
#define QUAT_H


#include <math.h>
#include "matrix4.h"
#include "vector3.h"


struct quatf
{
	float w, x, y, z;

	quatf() { reset(); }
	quatf(const float _x, const float _y, const float _z, const float _w) { set(_x, _y, _z, _w); }
	quatf(float t, const vector3f& axis) { set(t, axis); }

	inline void set(const float _x, const float _y, const float _z, const float _w)
	{
        x=_x;
        y=_y;
        z=_z;
        w=_w;
    }

	inline void set(float t, const vector3f& axis)
	{
		w = cosf(t/2);
		x = axis.x * sinf(t/2);
		y = axis.y * sinf(t/2);
		z = axis.z * sinf(t/2);
	}

	inline void reset()
	{
	    x=0.0f;
	    y=0.0f;
	    z=0.0f;
	    w=1.0f;
	}

	inline const quatf & operator = (const quatf &v)
	{
		w = v.w; x = v.x; y = v.y; z = v.z;
		return *this;
	}

	inline const quatf operator * (const quatf& q)
	{
		return quatf(
			w*q.x + x*q.w + y*q.z - z*q.y,
			w*q.y - x*q.z + y*q.w + z*q.x,
			w*q.z + x*q.y - y*q.x + z*q.w,
			w*q.w - x*q.x - y*q.y - z*q.z);
	}

	inline const quatf operator *= (const quatf &v)
	{
	    *this = *this * v;
	    return *this;
	}

	inline const quatf & operator *= (const float s)
	{
		w *= s; x *= s; y *= s; z *= s;
		return *this;
	}

	inline const quatf & operator /= (const float s)
	{
		w /= s; x /= s; y /= s; z /= s;
		return *this;
	}

	inline float length()
	{
		return sqrtf(w*w + x*x + y*y + z*z);
	}

	inline void normalize()
	{
		*this /= length();
	}

    //local rotation
	inline void rotateX(float rad)
	{
	    (*this) *= quatf(rad, vector3f(1, 0, 0));
    }
	inline void rotateY(float rad)
	{
	    (*this) *= quatf(rad, vector3f(0, 1, 0));
    }
	inline void rotateZ(float rad)
	{
	    (*this) *= quatf(rad, vector3f(0, 0, 1));
    }
    //global rotation
	inline void rotateGlobalX(float rad)
	{
	    (*this) *= quatf(rad, vector3f(1, 0, 0));
    }
	inline void rotateGlobalY(float rad)
	{
	    (*this) *= quatf(rad, vector3f(0, 1, 0));
    }
	inline void rotateGlobalZ(float rad)
	{
	    (*this) *= quatf(rad, vector3f(0, 0, 1));
    }

	matrix4f getMatrix() const;

	void getMatrix(matrix4f &m) const;
};


#endif // QUAT_H
