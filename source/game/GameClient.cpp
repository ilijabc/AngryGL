/*
 * GameClient.cpp
 *
 *  Created on: 03.04.2013.
 *      Author: idjukic
 */

#include "GameClient.h"

GameClient::GameClient(AppServer* server) : AppClient(server)
{
	mFont = new GLFont("data/arial.fnt");
}

GameClient::~GameClient()
{
	delete mFont;
}

void GameClient::onUpdate(float dt)
{
}

void GameClient::onDraw(GLView *view)
{
	//3D
	view->beginScene3D();
	view->endScene3D();
	//GUI
	view->beginGui(800, 600);
	glColor3f(1,1,1);
	view->drawRect(10, 10, 100, 100);
	mFont->drawString(10, 10, "Hello");
	view->endGui();
}

void GameClient::onKeyEvent(int key, int action)
{
}

void GameClient::onMouseMoveEvent(int x, int y)
{
}

void GameClient::onMouseButtonEvent(int button, int press)
{
}

void GameClient::onMouseWheelEvent(int wheel)
{
}

void GameClient::onSize(int width, int height)
{
}


