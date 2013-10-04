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
	mScene = new GameScene(this);
	mCamera = mScene->getCamera();
	mScene->addObject(new GameObject(mScene, 0));
	memset(mButtonState, 0, sizeof(int) * (GLFW_MOUSE_BUTTON_LAST + 1));
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
	mScene->draw(view);
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
    if (key == GLFW_KEY_ESC)
    {
    	getServer()->close();
    }
}

void GameClient::onMouseMoveEvent(int x, int y)
{
	int dx = x - mMousePos.x;
	int dy = y - mMousePos.y;
	if (mButtonState[GLFW_MOUSE_BUTTON_LEFT])
	{
		mCamera->rotation.z += dx;
		mCamera->rotation.x += dy;
	}
	mMousePos.x = x;
	mMousePos.y = y;
}

void GameClient::onMouseButtonEvent(int button, int press)
{
	mButtonState[button] = press;
}

void GameClient::onMouseWheelEvent(int wheel)
{
	int dz = wheel - mMousePos.z;
	mCamera->zoom += dz * 1.0f;
	mMousePos.z = wheel;
}

void GameClient::onSize(int width, int height)
{
}


