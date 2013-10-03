/*
 * GameClient.cpp
 *
 *  Created on: 19.10.2012.
 *      Author: idjukic
 */

#include "AppClient.h"
#include <string.h>

AppClient::AppClient(AppServer *server)
{
	mServer = server;
}

AppClient::~AppClient()
{
	for (std::list<GLTexture*>::iterator itex = mTexturePool.begin(); itex != mTexturePool.end(); itex++)
	{
		delete *itex;
	}
}

GLTexture *AppClient::getTexture(const char *filename, int flags)
{
	for (std::list<GLTexture*>::iterator itex = mTexturePool.begin(); itex != mTexturePool.end(); itex++)
	{
		GLTexture *tex = *itex;
		if (strcmp(tex->getFileName(), filename) == 0)
			return tex;
	}
	GLTexture *tex = new GLTexture(filename, flags);
	mTexturePool.push_back(tex);
	return tex;
}
