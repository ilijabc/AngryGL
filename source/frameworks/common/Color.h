#ifndef COLOR_H
#define COLOR_H


#include "common.h"


struct Color
{
	float red;
	float green;
	float blue;
	float alpha;

	Color() : red(0.0f), green(0.0f), blue(0.0f), alpha(1.0f) { }
	Color(float r, float g, float b) : red(r), green(g), blue(b), alpha(1.0f) { }
	Color(float r, float g, float b, float a) : red(r), green(g), blue(b), alpha(a) { }
	Color(unsigned int argb) { setHexColor(argb); }

	inline float* getPtr() { return &red; }

	void setHexColor(unsigned int argb);
	void addBrightness(int brightness);

	//common colors
	static Color Transparent;
	static Color White;
	static Color Black;
	static Color Red;
	static Color Green;
	static Color Blue;
	static Color Yellow;
	static Color Gray;
};


#endif // COLOR_H
