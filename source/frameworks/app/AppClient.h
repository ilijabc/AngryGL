/*
 * GameClient.h
 *
 *  Created on: 19.10.2012.
 *      Author: idjukic
 */

#ifndef APPCLIENT_H_
#define APPCLIENT_H_

#include "glplus/glplus.h"

#include <time.h>
#include <list>

#ifdef DEBUG
#define LOG(msg, args...) printf("[%d] "msg"\n", (int)time(NULL), ##args)
#define LOGE(msg, args...) printf("[%d] ERROR: "msg"\n", (int)time(NULL), ##args)
#else
#define LOG(args...)
#define LOGE(args...)
#endif

class AppServer;

class AppClient
{
public:
	AppClient(AppServer *server);
	virtual ~AppClient();
	//callbacks
	virtual void onUpdate(float dt) = 0;
	virtual void onDraw(GLView *view) = 0;
	virtual void onKeyEvent(int key, int action) = 0;
	virtual void onMouseMoveEvent(int x, int y) = 0;
	virtual void onMouseButtonEvent(int button, int press) = 0;
	virtual void onMouseWheelEvent(int wheel) = 0;
    virtual void onSize(int width, int height) = 0;
    //managers
    GLTexture *getTexture(const char *filename, int flags = 0);
    //getters
    inline AppServer* getServer() const { return mServer; }
private:
    AppServer *mServer;
    std::list<GLTexture*> mTexturePool;
};

#endif /* APPCLIENT_H_ */
