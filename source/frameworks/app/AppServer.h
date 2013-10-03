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

private:
	Settings mSettings;
	AppClient *mClient;
	GLView *mView;
	bool mRunning;
	bool *mKeyStatus;
};

#endif /* APPSERVER_H_ */
