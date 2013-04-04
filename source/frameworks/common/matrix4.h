#ifndef MATRIX4X4_H
#define MATRIX4X4_H


#include <math.h>

struct vector3f;


enum EMatrix4Construct
{
	eMatrixIdentity = 0,
	eMatrixRotateX,
	eMatrixRotateY,
	eMatrixRotateZ,
	eMatrixTranslate,
	eMatrixScale
};


class matrix4f
{
public:

	struct
	{
		float m11, m12, m13, m14;
		float m21, m22, m23, m24;
		float m31, m32, m33, m34;
		float m41, m42, m43, m44;
	};

	matrix4f()
	{
	    identity();
	}

	matrix4f(EMatrix4Construct make)
	{
        identity();
	}

	matrix4f(EMatrix4Construct make, float val)
	{
        identity();
		switch (make)
		{
		case eMatrixRotateX:
			setRotateX(val);
			break;
		case eMatrixRotateY:
			setRotateY(val);
			break;
		case eMatrixRotateZ:
			setRotateZ(val);
			break;
        case eMatrixScale:
            setScale(val);
        default:
            break;
		}
	}

	matrix4f(EMatrix4Construct make, float x, float y, float z)
	{
        identity();
	    if (make == eMatrixTranslate)
        {
            setTranslate(x, y, z);
        }
        else if (make == eMatrixScale)
        {
            setScale(x, y, z);
        }
	}

	matrix4f(float _m11, float _m12, float _m13, float _m14,
             float _m21, float _m22, float _m23, float _m24,
			 float _m31, float _m32, float _m33, float _m34,
			 float _m41, float _m42, float _m43, float _m44)
	{
		m11=_m11; m12=_m12; m13=_m13; m14=_m14;
		m21=_m21; m22=_m22; m23=_m23; m24=_m24;
		m31=_m31; m32=_m32; m33=_m33; m34=_m34;
		m41=_m41; m42=_m42; m43=_m43; m44=_m44;
	}

	matrix4f(float ma[16])
	{
		m11=ma[ 0]; m12=ma[ 1]; m13=ma[ 2]; m14=ma[ 3];
		m21=ma[ 4]; m22=ma[ 5]; m23=ma[ 6]; m24=ma[ 7];
		m31=ma[ 8]; m32=ma[ 9]; m33=ma[10]; m34=ma[11];
		m41=ma[12]; m42=ma[13]; m43=ma[14]; m44=ma[15];
	}

	void identity()
	{
		m11=1; m12=0; m13=0; m14=0;
		m21=0; m22=1; m23=0; m24=0;
		m31=0; m32=0; m33=1; m34=0;
		m41=0; m42=0; m43=0; m44=1;
	}

    void set(float _m11, float _m12, float _m13, float _m14,
			 float _m21, float _m22, float _m23, float _m24,
			 float _m31, float _m32, float _m33, float _m34,
			 float _m41, float _m42, float _m43, float _m44)
	{
		m11=_m11; m12=_m12; m13=_m13; m14=_m14;
		m21=_m21; m22=_m22; m23=_m23; m24=_m24;
		m31=_m31; m32=_m32; m33=_m33; m34=_m34;
		m41=_m41; m42=_m42; m43=_m43; m44=_m44;
	}

	const float* getElements() const { return &m11; }

	float getElement(int index) const
	{
		return (&m11)[index];
	}

	void setElement(float val, int index)
	{
		(&m11)[index] = val;
	}


	matrix4f operator * (const matrix4f& m) const;

	const matrix4f& operator *= (const matrix4f& m);

    //
	// Translate
    //

	void setTranslate(float x, float y, float z)
	{
		m41 = x;
		m42 = y;
		m43 = z;
	}

	void translate(float x, float y, float z)
	{
		*this = matrix4f(eMatrixTranslate, x, y, z) * (*this);
	}

    //
	// Rotate
    //

	void rotate(float t, const vector3f& axis);

	void setRotateX(float t)
	{
	    float st = sinf(t*0.017453f);
	    float ct = cosf(t*0.017453f);
        m22 =  ct;
        m23 =  st;
        m32 = -st;
        m33 =  ct;
	}

	void setRotateY(float t)
	{
	    float st = sinf(t*0.017453f);
	    float ct = cosf(t*0.017453f);
        m11 =  ct;
        m13 = -st;
        m31 =  st;
        m33 =  ct;
	}

	void setRotateZ(float t)
	{
	    float st = sinf(t*0.017453f);
	    float ct = cosf(t*0.017453f);
        m11 =  ct;
        m12 =  st;
        m21 = -st;
        m22 =  ct;
	}

	void rotateX(float t)
	{
	    *this = matrix4f(eMatrixRotateX, t) * (*this);
	}

	void rotateY(float t)
	{
	    *this = matrix4f(eMatrixRotateY, t) * (*this);
	}

	void rotateZ(float t)
	{
	    *this = matrix4f(eMatrixRotateZ, t) * (*this);
	}

	//
	// Scale
	//

	void setScale(float x, float y, float z)
	{
	    m11 = x;
	    m22 = y;
	    m33 = z;
	}

	void setScale(float s)
	{
	    m11 = s;
	    m22 = s;
	    m33 = s;
	}

	void scale(float x, float y, float z)
	{
	    *this = matrix4f(eMatrixScale, x, y, z) * (*this);
	}

	void scale(float s)
	{
	    *this = matrix4f(eMatrixScale, s) * (*this);
	}
};


#endif // MATRIX4X4_H
