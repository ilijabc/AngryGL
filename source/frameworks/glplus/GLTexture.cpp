#include "GLTexture.h"

#include "utils/stb_image.h"

#include <string.h>
#include <stdlib.h>

GLTexture::GLTexture()
{
    mTextureId = 0;
    mWidth = 0;
    mHeight = 0;
    mBPP = 0;
	strcpy(mFileName, "");
}

GLTexture::GLTexture(int w, int h, int flags)
{
    glGenTextures(1, &mTextureId);
    glBindTexture(GL_TEXTURE_2D, mTextureId);
    glEnable(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
    if (flags & GLPLUS_TEXTURE_EDGE)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h,
                 0, GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, 0);
    mWidth = w;
    mHeight = h;
    mBPP = 4;
	strcpy(mFileName, "");
}

GLTexture::GLTexture(const char *file_name, int flags, GLTextureFilterFuncPtr filterFunc, void *filterParam)
{
	int img_width = 0;
	int img_height = 0;
	int img_bpp = 0;
    unsigned char* img_data = stbi_load(file_name, &img_width, &img_height, &img_bpp, 4);

    if (img_data)
    {
        GLenum type = (img_bpp == 4) ? GL_RGBA : GL_RGB;
        mWidth = img_width;
        mHeight = img_height;
        mBPP = img_bpp;
		strcpy(mFileName, file_name);

		//only 32bit images (for now)
		type = GL_RGBA;
		mBPP = 4;

        glGenTextures(1, &mTextureId);
        glBindTexture(GL_TEXTURE_2D, mTextureId);

        //edge
        if (flags & GLPLUS_TEXTURE_EDGE)
        {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        }
        else if (flags & GLPLUS_TEXTURE_BORDER)
        {
            float c[4] = {1,1,1,1};
            glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, c);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        }

        //filter
        if (flags & GLPLUS_TEXTURE_NEAREST)
        {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        }
        else if (flags & GLPLUS_TEXTURE_LINEAR)
        {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        }
        else
        {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        }

        //filter function
        if (filterFunc)
        {
        	filterFunc(img_data, mWidth, mHeight, mBPP, filterParam);
        }

        //mipmaps
        if (flags & GLPLUS_TEXTURE_NOMIPMAPS)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, mBPP, mWidth, mHeight, 0,
                         type, GL_UNSIGNED_BYTE, img_data);
        }
        else
        {
            gluBuild2DMipmaps(GL_TEXTURE_2D, mBPP, mWidth, mHeight,
                              type, GL_UNSIGNED_BYTE, img_data);
        }
    }
	else
	{
		mTextureId = 0;
		mWidth = 0;
		mHeight = 0;
		mBPP = 0;
		strcpy(mFileName, "");
        printf("%s:%d: error: Loading texture '%s'\n", __FILE__, __LINE__, file_name);
	}
}

GLTexture::~GLTexture()
{
    if (mTextureId)
		glDeleteTextures(1, &mTextureId);
}

void GLTexture::push() const
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, mTextureId);
}

void GLTexture::pop() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
}

void GLTexture::drawImage(float x1, float y1, float x2, float y2, float u1, float v1, float u2, float v2) const
{
    GLfloat vert[12] = {
        x1,y1 , x2,y1 , x2,y2 ,
        x2,y2 , x1,y2 , x1,y1 };
    GLfloat texc[12] = {
        u1,v2 , u2,v2 , u2,v1 ,
        u2,v1 , u1,v1 , u1,v2 };

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, mTextureId);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, vert);
	glTexCoordPointer(2, GL_FLOAT, 0, texc);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisable(GL_TEXTURE_2D);
}


