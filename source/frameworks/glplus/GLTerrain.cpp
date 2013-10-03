/*
	by Ilija
*/


#include "GLTerrain.h"


void GLTerrain::init(int sizeX, int sizeY)
{
	int vx1 = 0;
	int vx2 = sizeX;
	int vy1 = 0;
	int vy2 = sizeX;
	for (int vx = vx1; vx <= vx2; vx++)
	{
		for (int vy = vy1; vy <= vy2; vy++)
		{
			//init vertex
			mVertexMap[vx][vy].height = 0.0f;
			mVertexMap[vx][vy].color = GLColor::White;
			//init map
			if (vx < sizeX && vy < sizeY)
			{
				mFaceMap[vx][vy].flags = 0;
				mFaceMap[vx][vy].texsrc.set(0, 0, 1, 1);
			}
		}
	}
	mSizeX = sizeX;
	mSizeY = sizeY;
	buildNormals();
}


void GLTerrain::generate(int steps, float size_min, float size_max, float h_min, float h_max)
{
	for (int i = 0; i < steps; i++)
	{
		float x = randomFloat(mSizeX);
		float y = randomFloat(mSizeY);
		float bsize = randomFloat(size_min, size_max);
		float dh = randomFloat(h_min, h_max);
		addHeight(x, y, bsize, dh);
	}

	buildNormals();
}


void GLTerrain::fillColor(GLColor c)
{
	for (int vx = 0; vx <= mSizeX; vx++)
	{
		for (int vy = 0; vy <= mSizeY; vy++)
		{
			mVertexMap[vx][vy].color = c;
		}
	}
}

void GLTerrain::addHeight(float x, float y, float bsize, float dh)
{
    int x1 = MAX((int)x-(int)bsize-2, 0);
    int y1 = MAX((int)y-(int)bsize-2, 0);
    int x2 = MIN((int)x+(int)bsize+2, mSizeX);
    int y2 = MIN((int)y+(int)bsize+2, mSizeY);
    for (int i=x1; i<=x2; i++)
    for (int j=y1; j<=y2; j++)
    {
        float r = DIST(x, y, i, j) * 2 / bsize;
        if (ABS(r) < 1.0)
        {
            mVertexMap[i][j].height += dh/2 + cos(r*3.14)*dh/2;
        }
    }
    //buildNormals();
}


void GLTerrain::addColor(float x, float y, float bsize, float rr, float gg, float bb)
{
    int x1 = MAX((int)x-(int)bsize-2, 0);
    int y1 = MAX((int)y-(int)bsize-2, 0);
    int x2 = MIN((int)x+(int)bsize+2, mSizeX);
    int y2 = MIN((int)y+(int)bsize+2, mSizeY);
    for (int i=x1; i<=x2; i++)
    for (int j=y1; j<=y2; j++)
    {
        float r = 1 - DIST(x, y, i, j) / bsize;
        if (r <= 1 && r >= 0)
        {
        	GLColor& cc = mVertexMap[i][j].color;
            cc.red = CLAMP(cc.red + (r * rr), 0, 1);
            cc.green = CLAMP(cc.green + (r * gg), 0, 1);
            cc.blue = CLAMP(cc.blue + (r * bb), 0, 1);
        }
    }
}


float GLTerrain::pickHeight(float x, float y)
{
	x = CLAMP(x, 0, mSizeX);
    y = CLAMP(y, 0, mSizeY);
    int ix = (int)x;
    int iy = (int)y;
    float xx = x - ix;
    float yy = y - iy;
    vector3f a1, a2, b1, b2;
    vector3f q0, q, p;

    //Q_0
    if (xx > yy)
		a1.set(1, 0, 0);
    else
		a1.set(0, 1, 0);
    a2.set(xx, yy, 0);
    b1.set(0, 0, 0);
    b2.set(1, 1, 0);
    if (!v3Intersect(q0, a1, a2, b1, b2)) return 0;
    //Q
    a1 = q0;
    a2.set(q0.x, q0.y, q0.z+1);
    b1.set(0, 0, mVertexMap[ix][iy].height);
    b2.set(1, 1, mVertexMap[ix+1][iy+1].height);
    if (!v3Intersect(q, a1, a2, b1, b2)) return 0;
    //P'
    a1 = q;
    if (xx > yy)
		a2.set(1, 0, mVertexMap[ix+1][iy].height);
    else
		a2.set(0, 1, mVertexMap[ix][iy+1].height);
    b1.set(xx, yy, 0);
    b2.set(xx, yy, 1);
    if (!v3Intersect(p, a1, a2, b1, b2)) return 0;

    return p.z;
}

void GLTerrain::render()
{
	render(0, 0, mSizeX, mSizeY);
}

void GLTerrain::render(float x1, float y1, float x2, float y2)
{
	int tx1 = CLAMP((int)x1, 0, mSizeX);
	int tx2 = CLAMP((int)x2, 0, mSizeY);
	int ty1 = CLAMP((int)y1, 0, mSizeY);
	int ty2 = CLAMP((int)y2, 0, mSizeY);

	// render ground
	if (mGroundTexture)
	{
		mGroundTexture->push();
		glBegin(GL_QUADS);
		for (int tx = tx1; tx < tx2; tx++)
		{
			for (int ty = ty1; ty < ty2; ty++)
			{
				if (mFaceMap[tx][ty].flags != 1)
				{
					setGLVertex(tx, ty, 0);
					setGLVertex(tx + 1, ty, 1);
					setGLVertex(tx + 1, ty + 1, 2);
					setGLVertex(tx, ty + 1, 3);
				}
			}
		}
		glEnd();
		mGroundTexture->pop();
	}

	// render water
	if (mWaterTexture)
	{
		float z = 0;
		float u1 = tx1;
		float v1 = ty1;
		float u2 = tx2;
		float v2 = ty2;
		mWaterTexture->push();
		glBegin(GL_QUADS);
		glColor4f(1, 1, 1, 1);
		glNormal3f(0, 0, 1);
		//A
		glTexCoord2f(u1, v1);
		glVertex3f(tx1, ty1, z);
		//B
		glTexCoord2f(u2, v1);
		glVertex3f(tx2, ty1, z);
		//C
		glTexCoord2f(u2, v2);
		glVertex3f(tx2, ty2, z);
		//D
		glTexCoord2f(u1, v2);
		glVertex3f(tx1, ty2, z);
		glEnd();
		mWaterTexture->pop();
	}

}

void GLTerrain::setGLVertex(int tx, int ty, int tex_index)
{
	float x = tx - mSizeX / 2;
	float y = ty - mSizeY / 2;
	float z = mVertexMap[tx][ty].height;
	vector3f v(
			x,
			y,
			sqrtf(x * x + y * y)
	);
	glColor4fv(mVertexMap[tx][ty].color.getPtr());
	glNormal3fv(mVertexMap[tx][ty].normal.getPtr());
	switch (tex_index)
	{
	case 0:
		glTexCoord2f(mFaceMap[tx][ty].texsrc.x1, mFaceMap[tx][ty].texsrc.y1);
		break;
	case 1:
		glTexCoord2f(mFaceMap[tx][ty].texsrc.x2, mFaceMap[tx][ty].texsrc.y1);
		break;
	case 2:
		glTexCoord2f(mFaceMap[tx][ty].texsrc.x2, mFaceMap[tx][ty].texsrc.y2);
		break;
	case 3:
		glTexCoord2f(mFaceMap[tx][ty].texsrc.x1, mFaceMap[tx][ty].texsrc.y2);
		break;
	}
	glVertex3f(v.x, v.y, v.z);
}

void GLTerrain::buildNormals()
{
	int nx1 = 0;
	int nx2 = TERRAIN_MAX_SIZE;
	int ny1 = 0;
	int ny2 = TERRAIN_MAX_SIZE;

	for (int tx = nx1; tx < nx2; tx++)
	{
		for (int ty = ny1; ty < ny2; ty++)
		{
			vector3f v1(tx, ty, mVertexMap[tx][ty].height);
			vector3f v2(tx+1, ty, mVertexMap[tx+1][ty].height);
			vector3f v3(tx+1, ty+1, mVertexMap[tx+1][ty+1].height);
			vector3f v4(tx, ty+1, mVertexMap[tx][ty+1].height);
			mFaceMap[tx][ty].normal1 = v3MakeFaceNormal(v1, v2, v3);
			mFaceMap[tx][ty].normal2 = v3MakeFaceNormal(v3, v4, v1);
		}
	}

	for (int vx = nx1; vx <= nx2; vx++)
	{
		for (int vy = ny1; vy <= ny2; vy++)
		{
			computeVerticeNormal(vx, vy);
		}
	}
}


void GLTerrain::computeVerticeNormal(int vx, int vy)
{
	vector3f& norm = mVertexMap[vx][vy].normal;
	int n = 0;

    if (vx > 0 && vy > 0)
    {
    	norm += mFaceMap[vx-1][vy-1].normal1;
    	norm += mFaceMap[vx-1][vy-1].normal2;
    	n += 2;
    }
    if (vx > 0 && vy < mSizeY)
    {
    	norm += mFaceMap[vx-1][vy].normal1;
    	n++;
    }
    if (vx < mSizeX && vy > 0)
    {
    	norm += mFaceMap[vx][vy-1].normal2;
    	n++;
    }
    if (vx < mSizeX && vy < mSizeY)
    {
    	norm += mFaceMap[vx][vy].normal1;
    	norm += mFaceMap[vx][vy].normal2;
    	n += 2;
    }

    norm /= (float)n;
    norm.normalize();
}


