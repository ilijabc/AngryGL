#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "GameCommon.h"

class GameScene;
class GameObject;

enum GameObjectType
{
	eGameObjectType = 0,
	eGameSpriteType
};

class IGameObjectBehavior
{
public:
	IGameObjectBehavior() { }
	virtual ~IGameObjectBehavior() { }
	// object behavior interface
	virtual void onUpdate(float dt) = 0;
	virtual void onDraw(GLView *view) = 0;
	// name
	inline const char *getName() const { return mName; }
	inline void setName(const char *name) { strcpy(mName, name); }
	// object
	inline GameObject *getObject() const { return mObject; }
	inline void setObject(GameObject *obj) { mObject = obj; }
private:
	char mName[260];
	GameObject *mObject;
};

class GameObject
{
public:
	GameObject(GameScene *scene, int type);
	virtual ~GameObject();
	void drawObject(GLView *view, const matrix4f &modelMatrix, unsigned int flags);
	void drawObjectShadow(GLView *view);
	//events
	virtual void onUpdate(float dt);
	virtual void onDraw(GLView *view, unsigned int flags);
	virtual void onDrawShadow(GLView *view);
    //setters
	inline void setPosition(const vector3f &pos) { mPosition = pos; }
	inline void setPosition(float x, float y, float z) { mPosition.set(x, y, z); }
	inline void setRotation(float rot) { mRotation.z = rot; }
	inline void setScale(float scale) { mScale.set(scale, scale, scale); }
	inline void setName(const char *name) { strcpy(mName, name); }
	inline void setShadow(bool shadow) { mHasShadow = shadow; }
	//getters
    inline int getType() const { return mType; }
    inline const vector3f &getPosition() const { return mPosition; }
    inline const vector3f &getRotation() const { return mRotation; }
    inline const vector3f &getScale() const { return mScale; }
    inline const char *getName() const { return mName; }
    inline GameScene *getScene() const { return mScene; }
    inline bool getShadow() const { return mHasShadow; }
    //behaviors
    template <class T> T addBehavior(const char *name)
    {
    	T bhv = new T();
    	bhv->setName(name);
    	bhv->setObject(this);
    	mBehaviorList.push_back(bhv);
    	return bhv;
    }
    IGameObjectBehavior *getBehavior(const char *name);

private:
    GameScene *mScene;
    int mType;
    vector3f mPosition;
    vector3f mRotation;
    vector3f mScale;
    matrix4f mModelMatrix;
    char mName[250];
    bool mHasShadow;
    std::list<IGameObjectBehavior*> mBehaviorList;
};

#endif // GAMEOBJECT_H
