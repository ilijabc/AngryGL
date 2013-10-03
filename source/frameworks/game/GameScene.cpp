/*
 * GameScene.cpp
 *
 *  Created on: 19.10.2012.
 *      Author: idjukic
 */

#include "GameScene.h"

GameScene::GameScene(AppClient *game)
		: mGame(game)
		, mDrawFlags(0xFFFFFFFF)
{
	mCamera.position.set(0, 0, 0);
	mCamera.rotation.x = -45;
	mCamera.zoom = -20;

	mTerrain = NULL;
	mSelectTexture = getGame()->getTexture("select.png");
}

GameScene::~GameScene()
{
	delete mTerrain;
}

void GameScene::update(float dt)
{
	for (std::list<GameObject*>::iterator iobj = mGameObjectList.begin(); iobj != mGameObjectList.end(); iobj++)
	{
		(*iobj)->onUpdate(dt);
	}
}

void GameScene::draw(GLView *view)
{
	mCamera.apply();
	if (mTerrain)
	{
#if 0
		mTerrain->render(
			mCamera.position.x - 22,
			mCamera.position.y - 9,
			mCamera.position.x + 22,
			mCamera.position.y + 21);
#else
		mTerrain->render();
#endif
	}
	mPickedPoint = view->pickPoint3D(mMouseX, mMouseY);
	//shadow
	for (std::list<GameObject*>::iterator iobj = mGameObjectList.begin(); iobj != mGameObjectList.end(); iobj++)
	{
		GameObject* obj = *iobj;
		if (obj->getShadow())
			obj->drawObjectShadow(view);
	}
	//object
	for (std::list<GameObject*>::iterator iobj = mGameObjectList.begin(); iobj != mGameObjectList.end(); iobj++)
	{
		GameObject* obj = *iobj;
		obj->drawObject(view, mSceneMatrix, mDrawFlags);
	}
}

GameObject *GameScene::addObject(GameObject *obj, bool to_back)
{
	if (to_back)
		mGameObjectList.push_back(obj);
	else
		mGameObjectList.push_front(obj);
	return obj;
}

GameObject *GameScene::getObjectByName(const char *name)
{
	for (std::list<GameObject*>::iterator iobj = mGameObjectList.begin(); iobj != mGameObjectList.end(); iobj++)
	{
		if (strcmp((*iobj)->getName(), name) == 0)
			return (*iobj);
	}
	return NULL;
}
