/*
 * GameMain.cpp
 *
 *  Created on: 03.04.2013.
 *      Author: idjukic
 */

#include "GameClient.h"

int main(int argc, char **argv)
{
	AppServer *server = AppServer::init("TEST 1.0", "settings.ini");
	GameClient *game = new GameClient(server);

	server->run(game);

	delete game;
	delete server;
}
