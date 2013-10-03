/*
 * GameClient.h
 *
 *  Created on: 03.04.2013.
 *      Author: idjukic
 */

#ifndef GAMECLIENT_H_
#define GAMECLIENT_H_

#include "app/AppClient.h"
#include "app/AppServer.h"

class GameClient : public AppClient
{
public:
	GameClient(AppServer *server);
	virtual ~GameClient();
	//callbacks
	virtual void onUpdate(float dt);
	virtual void onDraw(GLView *view);
	virtual void onKeyEvent(int key, int action);
	virtual void onMouseMoveEvent(int x, int y);
	virtual void onMouseButtonEvent(int button, int press);
	virtual void onMouseWheelEvent(int wheel);
	virtual void onSize(int width, int height);

private:
	GLFont *mFont;
};

#endif /* GAMECLIENT_H_ */
