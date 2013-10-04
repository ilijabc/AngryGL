/*
 * AppServer.h
 *
 *  Created on: 29.01.2013.
 *      Author: idjukic
 */

#ifndef APPSERVER_H_
#define APPSERVER_H_

#include "AppClient.h"


class AppServer
{
public:
	struct Settings
	{
		int width;
		int height;
		int fullscreen;
		int desktop;
		int audio;
	};

	enum EventType
	{
		eKeyEventType = 0,
		eMousePosEventType,
		eMouseButtonEventType,
		eMouseWheelEventType,
		eWindowSizeEventType
	};

private:
	struct Event
	{
		Event(EventType t, int a1, int a2) : type(t), arg1(a1), arg2(a2) { }
		EventType type;
		int arg1;
		int arg2;
	};

public:
	static AppServer *init(const char *title, const char *settings_path);
	virtual ~AppServer();
	int run(AppClient* client);
	//getters
	Settings getSettings() const { return mSettings; }
	AppClient *getClient() const { return mClient; }
	inline bool getKeyStatus(int key) { return (mKeyStatus == NULL) ? false : mKeyStatus[key]; }
	//setters
	inline void setKeyStatus(int key, int status) { if (mKeyStatus) mKeyStatus[key] = status; }
	void sendEvent(EventType type, int arg1, int arg2);
	void close();

private:
	Settings mSettings;
	AppClient *mClient;
	GLView *mView;
	bool mRunning;
	bool *mKeyStatus;
	std::vector<Event> mEventList;
};

#endif /* APPSERVER_H_ */
