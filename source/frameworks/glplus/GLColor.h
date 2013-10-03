/*
 * GLColor.h
 *
 *  Created on: 09.08.2013.
 *      Author: idjukic
 */

#ifndef GLCOLOR_H_
#define GLCOLOR_H_

class GLColor
{
public:
	static GLColor Transparent;
	static GLColor White;
	static GLColor Black;
	static GLColor Gray;
	static GLColor Red;
	static GLColor Green;
	static GLColor Blue;
	static GLColor Yellow;

public:
	GLColor() { }
	GLColor(int ARGB) :
		red( ((ARGB >> 16) & 0xFF) / 255.0f ),
		green( ((ARGB >> 8) & 0xFF) / 255.0f ),
		blue( ((ARGB >> 0) & 0xFF) / 255.0f ),
		alpha( ((ARGB >> 24) & 0xFF) / 255.0f)
	{ }
	GLColor(float r, float g, float b, float a = 1.0f) :
		red(r),
		green(g),
		blue(b),
		alpha(a)
	{ }
	virtual ~GLColor() { }

	inline const float* getPtr() const { return &red; }

	float red;
	float green;
	float blue;
	float alpha;
};

#endif /* GLCOLOR_H_ */
