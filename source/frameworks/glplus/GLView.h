#ifndef GLVIEW_H
#define GLVIEW_H

#include "glplus_private.h"

class GLView
{
public:
	enum DrawingMode
	{
		Quads = 0,
		Triangles,
		Lines,
		LineLoop
	};

private:
	class IVertex
	{
	public:
		IVertex* normal(float x, float y, float z);
		IVertex* color(unsigned int rgba);
		IVertex* texcoord(float u, float v);
		friend class GLView;
	};

public:
	GLView();
	virtual ~GLView();
	
	void setup();
	
	void beginGui(int width = 0, int height = 0);
	void endGui();
	
	void beginScene2D(float left, float right, float bottom, float top);
	float beginScene2DWide(float height);
	void endScene2D();
	
	void beginScene3D();
	void endScene3D();
	
	void drawRect(float x1, float y1, float x2, float y2);
	void drawCube(float sx, float sy, float sz, float *color_array = 0);

	void setSize(int width, int height);
	int getWidth() const { return mWidth; }
	int getHeight() const { return mHeight; }

	//void renderCube(float x, float y, float z);
	//void pushTexture(GLTexture *tex);
	//void popTexture();
	//void multMatrix(const matrix4f& mat);
	//void setColor(Color c);
	//void beginPicking(int x, int y, float sense);
	//int endPicking();
	vector3f pickPoint3D(int x, int y);
	vector2f pickPoint2D(float x, float y, float z);

	// intermetiate mode
	void begin(DrawingMode mode);
	IVertex* vertex(float x, float y, float z);
	void end();

private:
	float mPerspectiveNear;
	float mPerspectiveFar;
	float mPerspectiveFOV;
	int mWidth;
	int mHeight;
};

#endif //GLVIEW_H
