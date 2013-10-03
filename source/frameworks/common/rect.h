#ifndef RECT_H
#define RECT_H


#include "mymath.h"
#include "vector2.h"


template <typename T>
struct rect
{
	rect() { }
	rect(T _x1, T _y1, T _x2, T _y2) : x1(_x1), y1(_y1), x2(_x2), y2(_y2) { }
	template <typename TT> rect(const rect<TT>& r) : x1(r.x1), y1(r.y1), x2(r.x2), y2(r.y2) { }

	static inline rect<T> bySize(T x, T y, T w, T h) { return rect<T>(x, y, x + w, y + h); }
	static inline rect<T> byCenter(T cx, T cy, T w, T h) { return rect<T>(cx - w/2, cy - h/2, cx + w/2, cy + h/2); }
	static inline rect<T> byNullCenter(const vector2<T> &v) { return rect<T>(-v.x/2, -v.y/2, v.x/2, v.y/2); }

	void set(T _x1, T _y1, T _x2, T _y2) { x1 = _x1; y1 = _y1; x2 = _x2; y2 = _y2; }
	void setBySize(T x, T y, T w, T h) { set(x, y, x + w, y + h); }
	void setByCenter(T cx, T cy, T w, T h) { set(cx - w/2, cy - h/2, cx + w/2, cy + h/2); }

	bool isPointInside(const vector2<T>& p) const
	{
		if (p.x < x1 || p.y < y1 || p.x > x2 || p.y > y2)
			return false;
		return true;
	}

    void fixSize()
    {
        if (x1 > x2) SWAP<float>(x1, x2);
        if (y1 > y2) SWAP<float>(y1, y2);
    }

	vector2<T> getCenter() const { return vector2<T>((x1 + x2) / 2, (y1 + y2) / 2); }
	T getWidth() const { return fabs(x1 - x2); }
	T getHeight() const { return fabs(y1 - y2); }

	void translate(T dx, T dy) { x1 += dx; y1 += dy; x2 += dx; y2 += dy; }

	void clip(const rect& r) { if(x1<r.x1)x1=r.x1; if(y1<r.y1)y1=r.y1; if(x2>r.x2)x2=r.x2; if(y2>r.y2)y2=r.y2; }

	T x1, y1, x2, y2;
};


typedef rect<int> recti;

typedef rect<float> rectf;


#endif // RECT_H
