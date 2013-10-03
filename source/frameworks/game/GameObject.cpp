#include "GameObject.h"
#include "GameScene.h"

//#define ENABLE_GAME_OBJECT_DRAW_DEBUG

GameObject::GameObject(GameScene *scene, int type)
		: mScene(scene)
		, mType(type)
		, mPosition(0, 0, 0)
		, mRotation(0, 0, 0)
		, mScale(1, 1, 1)
		, mHasShadow(false)
{
	strcpy(mName, "");
}

GameObject::~GameObject()
{
}

void GameObject::drawObject(GLView *view, const matrix4f &modelMatrix, unsigned int flags)
{
#if 0
    matrix4f m(eMatrixTranslate, mPosition.x, mPosition.y, mPosition.z);
    m.rotateX(mRotation.x);
    m.rotateY(mRotation.y);
    m.rotateZ(mRotation.z);
    //m.scale(mScale.x, mScale.y, mScale.z);
    mModelMatrix = m * modelMatrix;
    //gl draw
    glPushMatrix();
    glMultMatrix(m);
    onDraw(view, flags);
    glPopMatrix();
#else
    glPushMatrix();
    glTranslatef(mPosition.x, mPosition.y, mPosition.z);
    glRotatef(mRotation.x, 1, 0, 0);
    glRotatef(mRotation.y, 0, 1, 0);
    glRotatef(mRotation.z, 0, 0, 1);
    glScalef(mScale.x, mScale.y, mScale.z);
    onDraw(view, flags);
    glPopMatrix();
#endif
}

void GameObject::drawObjectShadow(GLView *view)
{
    glPushMatrix();
    glTranslatef(mPosition.x, mPosition.y, mPosition.z);
    glRotatef(mRotation.x, 1, 0, 0);
    glRotatef(mRotation.y, 0, 1, 0);
    glRotatef(mRotation.z, 0, 0, 1);
    glScalef(mScale.x, mScale.y, mScale.z);
    onDrawShadow(view);
    glPopMatrix();
}

void GameObject::onUpdate(float dt)
{
	for (std::list<IGameObjectBehavior*>::iterator ibhv = mBehaviorList.begin(); ibhv != mBehaviorList.end(); ibhv++)
	{
		(*ibhv)->onUpdate(dt);
	}
}

void GameObject::onDraw(GLView *view, unsigned int flags)
{
	for (std::list<IGameObjectBehavior*>::iterator ibhv = mBehaviorList.begin(); ibhv != mBehaviorList.end(); ibhv++)
	{
		(*ibhv)->onDraw(view);
	}
	view->drawCube(1, 1, 1);
}

void GameObject::onDrawShadow(GLView *view)
{

}

IGameObjectBehavior *GameObject::getBehavior(const char *name)
{
	for (std::list<IGameObjectBehavior*>::iterator ibhv = mBehaviorList.begin(); ibhv != mBehaviorList.end(); ibhv++)
	{
		if (strcmp((*ibhv)->getName(), name) == 0)
		{
			return (*ibhv);
		}
	}
	return NULL;
}
