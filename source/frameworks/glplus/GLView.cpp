#include "GLView.h"

GLView::GLView()
{
	mPerspectiveNear = 0.1;
	mPerspectiveFar = 10000.0;
	mPerspectiveFOV = 45.0;
}

GLView::~GLView()
{
}

void GLView::setup()
{
    //glInitExtensions();
	glClearColor(0, 0, 0, 0);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthFunc(GL_LEQUAL);
    glAlphaFunc(GL_GREATER, 0.1);    // for trees
    glShadeModel(GL_SMOOTH);
    //light
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    float lightPos[] = {0.0, 0.0, 1.0, 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
}

void GLView::beginGui(int width, int height)
{
	if (width == 0) width = mWidth;
	if (height == 0) height = mHeight;
	//attribs
	glPushAttrib(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_ENABLE_BIT | GL_CURRENT_BIT);
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_CULL_FACE);
	glColor3f(1, 1, 1);
	//projection
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, width, height, 0);
	//view
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
}

void GLView::endGui()
{
	glPopAttrib();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void GLView::beginScene2D(float left, float right, float bottom, float top)
{
	//attribs
	glPushAttrib(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_ENABLE_BIT | GL_CURRENT_BIT);
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_CULL_FACE);
	glColor3f(1, 1, 1);
	//projection
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(left, right, bottom, top, -1.0f, 1.0f);
	//view
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
}

float GLView::beginScene2DWide(float height)
{
	float aspect = (float)mWidth / (float)mHeight;
	float ww = height * aspect / 2;
	float hh = height / 2;
	beginScene2D(-ww, ww, -hh, hh);
	return ww * 2;
}

void GLView::endScene2D()
{
	glPopAttrib();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void GLView::beginScene3D()
{
	//attribs
	glPushAttrib(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_ENABLE_BIT | GL_CURRENT_BIT);
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_CULL_FACE);
	glColor3f(1, 1, 1);
	//calculate aspect
	int view[4];
	glGetIntegerv(GL_VIEWPORT, view);
	float aspect = (float)view[2]/(float)view[3];
	//perspective
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluPerspective(mPerspectiveFOV, aspect, mPerspectiveNear, mPerspectiveFar);
	//view
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
}

void GLView::endScene3D()
{
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glPopAttrib();
	glMatrixMode(GL_MODELVIEW);
}

void GLView::drawRect(float x1, float y1, float x2, float y2)
{
	glBegin(GL_LINE_LOOP);
	glVertex2f(x1, y1);
	glVertex2f(x2, y1);
	glVertex2f(x2, y2);
	glVertex2f(x1, y2);
	glEnd();
}

void GLView::drawCube(float sx, float sy, float sz, float *color_array)
{
	float x = sx / 2;
	float y = sy / 2;
	float z = sz / 2;
	static float vertices[72] = {
			-x, -y, -z,    x, -y, -z,    x, -y,  z,   -x, -y,  z,	//front
			 x, -y, -z,    x,  y, -z,    x,  y,  z,    x, -y,  z,	//right
			 x,  y, -z,	  -x,  y, -z,   -x,  y,  z,    x,  y,  z,	//back
			-x,  y, -z,   -x, -y, -z,   -x, -y,  z,   -x,  y,  z,	//left
			-x, -y,  z,    x, -y,  z,    x,  y,  z,   -x,  y,  z,	//top
			-x, -y, -z,   -x,  y, -z,    x,  y, -z,    x, -y, -z	//bottom
	};
	static float normals[72] = {
			 0, -1,  0,    0, -1,  0,    0, -1,  0,    0, -1,  0,   //front
			 1,  0,  0,    1,  0,  0,    1,  0,  0,    1,  0,  0,   //right
			 0,  1,  0,    0,  1,  0,    0,  1,  0,    0,  1,  0,   //back
			-1,  0,  0,   -1,  0,  0,   -1,  0,  0,   -1,  0,  0,   //left
			 0,  0,  1,    0,  0,  1,    0,  0,  1,    0,  0,  1,   //top
			 0,  0, -1,    0,  0, -1,    0,  0, -1,    0,  0, -1    //bottom
	};
	static float colors[72];
	if (color_array)
	{
		for (int i = 0; i < 72; i++)
		{
			colors[i] = color_array[(i / 12) * 3 + (i % 3)];
		}
	}
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	if (color_array)
		glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glNormalPointer(GL_FLOAT, 0, normals);
	if (color_array)
		glColorPointer(3, GL_FLOAT, 0, colors);
	glDrawArrays(GL_QUADS, 0, 24);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	if (color_array)
		glDisableClientState(GL_COLOR_ARRAY);
}

void GLView::setSize(int width, int height)
{
	glViewport(0, 0, width, height);
	mWidth = width;
	mHeight = height;
}

vector3f GLView::pickPoint3D(int x, int y)
{
    double modelview[16], projection[16];
    int viewport[4];
    float z;
	double vx, vy, vz;

    glGetDoublev( GL_PROJECTION_MATRIX, projection );
    glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
    glGetIntegerv( GL_VIEWPORT, viewport );

    glReadPixels( x, viewport[3]-y, 1, 1,
		 GL_DEPTH_COMPONENT, GL_FLOAT, &z );

    gluUnProject( x, viewport[3]-y, z, modelview,
		projection, viewport, &vx, &vy, &vz );

	return vector3f(vx, vy, vz);
}

vector2f GLView::pickPoint2D(float x, float y, float z)
{
    double modelview[16], projection[16];
    int viewport[4];
	double vx, vy, vz;

    glGetDoublev( GL_PROJECTION_MATRIX, projection );
    glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
    glGetIntegerv( GL_VIEWPORT, viewport );

    gluProject(x, y, z, modelview, projection, viewport, &vx, &vy, &vz);

    return vector2f(vx, viewport[3] - vy);
}

