/*
 * GameScene.h
 *
 *  Created on: 19.10.2012.
 *      Author: idjukic
 */

#ifndef GAMESCENE_H_
#define GAMESCENE_H_

#include "GameCommon.h"
#include "GameObject.h"
#include "GameTerrain.h"
#include "App/AppClient.h"

class GameScene
{
public:
	GameScene(AppClient *game);
	virtual ~GameScene();
	//control
	void update(float dt);
	void draw(GLView *view);
	GameObject *addObject(GameObject *obj, bool to_back = true);
	GameObject *getObjectByName(const char *name);
	//setters
	inline void setDrawFlags(unsigned int flags) { mDrawFlags = flags; }
	inline void setTerrain(GLTerrain *terrain) { mTerrain = terrain; }
	//getters
    inline AppClient *getGame() const { return mGame; }
    inline unsigned int getDrawFlags() const { return mDrawFlags; }
    inline GLTerrain *getTerrain() const { return mTerrain; }
    inline vector3f getWorldPoint(int x, int y) { mMouseX = x; mMouseY = y; return mPickedPoint; }
    inline GLCamera *getCamera() { return &mCamera; }
    inline GLTexture *getSelectTexture() const { return mSelectTexture; }

private:
    AppClient *mGame;
	std::list<GameObject*> mGameObjectList;
	unsigned int mDrawFlags;
	matrix4f mSceneMatrix;
	GLTerrain *mTerrain;
	vector3f mPickedPoint;
	int mMouseX;
	int mMouseY;
	GLCamera mCamera;
	GLTexture *mSelectTexture;
};

#endif /* GAMESCENE_H_ */
