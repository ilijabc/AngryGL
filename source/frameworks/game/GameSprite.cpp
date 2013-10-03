/*
 * GameSprite.cpp
 *
 *  Created on: 22.02.2013.
 *      Author: idjukic
 */

#include "GameSprite.h"
#include "GameScene.h"

GameSprite::GameSprite(GameScene *scene)
		: GameObject(scene, eGameSpriteType)
{
	mTexture = NULL;
	mSprite = NULL;
	mCurrentAnimation = NULL;
	mFrameIndex = 0;
	mFrameTimer = 0;
	mScaleImage = 1;
	mSelected = false;
	mAnimating = false;
}

GameSprite::~GameSprite()
{
}

void GameSprite::setSprite(GLSprite *sprite)
{
	mSprite = sprite;
	mCurrentAnimation = mSprite->getAnimation(mSprite->findAnimationIndex("walk_N"));
	mFrameIndex = 0;
	mFrameTimer = mCurrentAnimation->frames[0].delay / 50.0f;
	//scale by first frame
	mScaleImage = 1.0f / (float)mSprite->getSpriteInfo()->getFrameByIndex(0)->w;
}

void GameSprite::setTexture(GLTexture *tex)
{
	mTexture = tex;
}

void GameSprite::onUpdate(float dt)
{
	if (mCurrentAnimation && mAnimating)
	{
		mFrameTimer -= dt;
		if (mFrameTimer <= 0)
		{
			mFrameIndex++;
			if (mFrameIndex == mCurrentAnimation->framesCount)
				mFrameIndex = 0;
			mFrameTimer += mCurrentAnimation->frames[mFrameIndex].delay / 50.0f;
		}
	}
}

void GameSprite::onDraw(GLView* view, unsigned int flags)
{
	GLTexture *tex = mTexture;
	GLCamera *camera = getScene()->getCamera();
	if (tex == NULL)
		tex = mSprite->getTexture();
	glEnable(GL_ALPHA_TEST);
	glDisable(GL_LIGHTING);
	glTranslatef(0, 0, 0.1);
	if (mSelected)
	{
		getScene()->getSelectTexture()->drawImage(
				-0.4, -0.4, 0.4, 0.4,
				0, 0, 1, 1);
	}
	glRotatef(-camera->rotation.z, 0, 0, 1);
	//glRotatef(90, 1, 0, 0);
	glRotatef(-camera->rotation.x, 1, 0, 0);
	glScalef(mScaleImage, mScaleImage, mScaleImage);
	if (mSprite)
	{
		glColor3f(1, 1, 1);
		mSprite->drawFrame(tex, mCurrentAnimation->index, mFrameIndex);
	}
	else if (mTexture)
	{
		glColor3f(1, 1, 1);
		mTexture->drawImage(
				-1, 0, 1, 2,
				0, 0, 1, 1);
	}
	glDisable(GL_ALPHA_TEST);
	glEnable(GL_LIGHTING);
}

void GameSprite::onDrawShadow(GLView *view)
{
	GLCamera *camera = getScene()->getCamera();
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	//glTranslatef(0, 0, 0.05);
	//glRotatef(-camera->rotation.z, 0, 0, 1);
	//glRotatef(5, 1, 0, 0);
	glScalef(mScaleImage, mScaleImage, mScaleImage);
	if (mSprite)
	{
	}
	else if (mTexture)
	{
		glColor4f(0, 0, 0, 0.8);
		mTexture->drawImage(
				-1, 0, 1, 1,
				0, 0, 1, 1);
	}
	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
}

