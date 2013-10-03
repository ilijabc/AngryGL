/*
 * GameTerrain.cpp
 *
 *  Created on: 20.02.2013.
 *      Author: idjukic
 */

#include "GameTerrain.h"

GameTerrain::GameTerrain()
{
	mTerrain = new GLTerrain();
	mTerrain->init(100, 100);
	mTerrain->generate(200, 10, 2, 0, 3);
	mTerrain->buildNormals();
	//mPosition.set(-50, -50, 0);
}

GameTerrain::~GameTerrain()
{
	delete mTerrain;
}

void GameTerrain::draw()
{
	glPushMatrix();
	//glTranslatef(mPosition.x, mPosition.y, mPosition.z);
	mTerrain->render();
	glPopMatrix();
}

float GameTerrain::getHeight(float x, float y)
{
	//return mTerrain->pickHeight(x - mPosition.x, y - mPosition.y);
}
