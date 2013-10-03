#ifndef GLTEXTURE_H
#define GLTEXTURE_H

#include "glplus_private.h"

#define GLPLUS_TEXTURE_EDGE	       	 0x1
#define GLPLUS_TEXTURE_NOMIPMAPS     0x2
#define GLPLUS_TEXTURE_BORDER        0x4
#define GLPLUS_TEXTURE_NEAREST       0x8
#define GLPLUS_TEXTURE_LINEAR        0x10

typedef void (*GLTextureFilterFuncPtr)(unsigned char *img_data, int img_w, int img_h, int img_bpp, void *param);

class GLTexture
{
public:
	GLTexture();
	GLTexture(int w, int h, int flags = 0);
	GLTexture(const char* file_name, int flags = 0, GLTextureFilterFuncPtr filterFunc = 0, void *filterParam = 0);
	virtual ~GLTexture();

	void push() const;
	void pop() const;
	void drawImage(float x1, float y1, float x2, float y2, float u1, float v1, float u2, float v2) const;

	//getters
	inline GLuint getTextureId() const { return mTextureId; }
	inline int getWidth() const { return mWidth; }
	inline int getHeight() const { return mHeight; }
	inline int getBPP() const { return mBPP; }
	inline const char* getFileName() const { return mFileName; }

private:
	GLuint mTextureId;
	GLsizei mWidth;
	GLsizei mHeight;
	GLint mBPP;
	char mFileName[260];
};

#endif // GLTEXTURE_H
