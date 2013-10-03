#ifndef GLCAMERA_H
#define GLCAMERA_H

#include <GL/gl.h>
#include "common/vector3.h"


class GLCamera
{
public:
	GLCamera();
	virtual ~GLCamera();

	void apply();

	void translate2D(const float x, const float y);
	void lookAt(const float x, const float y, const float z);

	vector3f position;
	vector3f rotation;
	float zoom;
};


#endif // GLCAMERA_H
