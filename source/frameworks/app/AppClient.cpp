/*
 * GameClient.cpp
 *
 *  Created on: 19.10.2012.
 *      Author: idjukic
 */

#include "AppClient.h"
#include <string.h>

AppClient::AppClient(AppServer *server)
{
	mServer = server;
}

AppClient::~AppClient()
{
}
