/*
 * GameSprite.h
 *
 *  Created on: 22.02.2013.
 *      Author: idjukic
 */

#ifndef GAMESPRITE_H_
#define GAMESPRITE_H_

#include "GameObject.h"

class GameSprite: public GameObject
{
public:
	GameSprite(GameScene *scene);
	virtual ~GameSprite();
	//events
	virtual void onUpdate(float dt);
	virtual void onDraw(GLView *view, unsigned int flags);
	virtual void onDrawShadow(GLView *view);
	//setters
	void setSprite(GLSprite *sprite);
	void setTexture(GLTexture *tex);
	inline void setSelected(bool sel) { mSelected = sel; }
	//getters
	inline GLTexture *getTexture() const { return mTexture; }
	//animation
	inline void pauseAnimation() { mAnimating = false; }
	inline void resumeAnimation() { mAnimating = true; }
	inline void stopAnimation() { mAnimating = false; mFrameIndex = 0; }

private:
	GLSprite *mSprite;
	GLTexture *mTexture;
	GLSprite::Animation *mCurrentAnimation;
	int mFrameIndex;
	float mFrameTimer;
	float mScaleImage;
	bool mSelected;
	bool mAnimating;
};

#endif /* GAMESPRITE_H_ */
