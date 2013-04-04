/****************************************
 * By Will Perone
 * Original: 9-16-2002
 * Revised: 19-11-2003
 *          18-12-2003
 *          06-06-2004
 ****************************************/

#ifndef VECTOR2_H
#define VECTOR2_H

#include <math.h>


template <typename T>
struct vector2
{
	T x, y;

	//! trivial ctor
	vector2<T>(): x((T)0), y((T)0) {}

	//! setting ctor
	vector2<T>(const T x0, const T y0): x(x0), y(y0) {}

	vector2<T>(const vector2<T>& v): x(v.x), y(v.y) {}

	template <typename TT> vector2<T>(const vector2<TT>& v): x((T)v.x), y((T)v.y) {}

	//! array indexing
	T &operator [](unsigned int i)
	{   return *(&x+i);   }

	//! array indexing
	const T &operator [](unsigned int i) const
	{	return *(&x+i);   }

	//! function call operator
	void operator ()(const T x0, const T y0)
	{	x= x0; y= y0;	}

    //! sets value
    void set(const T x0, const T y0)
    {   x = x0; y = y0; }

	//! test for equality
	bool operator==(const vector2<T> &v) const
	{	return (x==v.x && y==v.y);	}

	//! test for inequality
	bool operator!=(const vector2<T> &v) const
	{	return (x!=v.x || y!=v.y);	}

	//! set to value
	const vector2<T> &operator =(const vector2<T> &v)
	{
		x= v.x; y= v.y;
		return *this;
	}

	//! negation
	const vector2<T> operator -(void) const
	{	return vector2<T>(-x, -y);	}

	//! addition
	const vector2<T> operator +(const vector2<T> &v) const
	{	return vector2<T>(x+v.x, y+v.y);	}

	//! subtraction
	const vector2<T> operator -(const vector2<T> &v) const
	{   return vector2<T>(x-v.x, y-v.y);	}

	//! uniform scaling
	const vector2<T> operator *(const T num) const
	{
		vector2<T> temp(*this);
		return temp*=num;
	}

	//! uniform scaling
	const vector2<T> operator /(const T num) const
	{
		vector2<T> temp(*this);
		return temp/=num;
	}

	//! addition
	const vector2<T> &operator +=(const vector2<T> &v)
	{
		x+=v.x;	y+=v.y;
		return *this;
	}

	//! subtraction
	const vector2<T> &operator -=(const vector2<T> &v)
	{
		x-=v.x;	y-=v.y;
		return *this;
	}

	//! uniform scaling
	const vector2<T> &operator *=(const T num)
	{
		x*=num;	y*=num;
		return *this;
	}

	//! uniform scaling
	const vector2<T> &operator /=(const T num)
	{
		x/=num;	y/=num;
		return *this;
	}

	//! dot product
	T operator *(const vector2<T> &v) const
	{	return x*v.x + y*v.y;	}
};


// macro to make creating the ctors for derived vectors easier
#define VECTOR2_CTORS(name, type)   \
	/* trivial ctor */				\
	name() {}						\
	/* down casting ctor */			\
	name(const vector2<type> &v): vector2<type>(v.x, v.y) {}	\
	/* make x,y combination into a vector */					\
	name(type x0, type y0): vector2<type>(x0, y0) {}



struct vector2i: public vector2<int>
{
	VECTOR2_CTORS(vector2i, int)
};


struct vector2ui: public vector2<unsigned int>
{
	VECTOR2_CTORS(vector2ui, unsigned int)
};


struct vector2f: public vector2<float>
{
	VECTOR2_CTORS(vector2f, float)

	vector2f(const vector2i& vi) { x = ((float)vi.x); y = ((float)vi.y); }

	//! gets the length of this vector squared
	float length_squared() const
	{	return (float)(*this * *this);   }

	//! gets the length of this vector
	float length() const
	{	return (float)sqrt(*this * *this);   }

	//! normalizes this vector
	void normalize()
	{	*this/=length();	}

	//! returns the normalized vector
	vector2f normalized() const
	{   return  *this/length();  }

	vector2f normalized(float d) const
	{   return  *this/length() * d;  }

	//! reflects this vector about n
	void reflect(const vector2f &n)
	{
		vector2f orig(*this);
		project(n);
		*this= *this*2 - orig;
	}

	//! projects this vector onto v
	void project(const vector2f &v)
	{	*this= v * (*this * v)/(v*v);	}

	//! returns this vector projected onto v
	vector2f projected(const vector2f &v) const
	{   return v * (*this * v)/(v*v);	}

	//! computes the angle between 2 arbitrary vectors
	static inline float angle(const vector2f &v1, const vector2f &v2)
	{   return acosf((v1*v2) / (v1.length()*v2.length()));  }

	//! computes the angle between 2 normalized arbitrary vectors
	static inline float angle_normalized(const vector2f &v1, const vector2f &v2)
	{   return acosf(v1*v2);  }

	//
	//by Ilija
	//

	inline float angle() const
	{
		return atan2f(y, x);
	}

	inline bool isNull() const
	{
		if (x == 0 && y == 0)
			return true;
		return false;
	}

	inline void normalize(float s)
	{
		*this /= (length() / s);
	}

	inline vector2f getRotated(const float a)
	{
		return vector2f(x * cosf(a) - y * sinf(a), x * sinf(a) + y * cosf(a));
	}

	inline vector2f getNormal()
	{
		return vector2f(-y, x);
	}

	inline float* getPtr() { return &x; }

	inline const float* const getConstPtr() const { return &x; }
};


#endif //VECTOR2_H
