/*
 * GameMain.cpp
 *
 *  Created on: 03.04.2013.
 *      Author: idjukic
 */

#include "GameClient.h"

int main(int argc, char **argv)
{
	AppServer *server = new AppServer("settings.ini");
	GameClient *game = new GameClient(server);

	server->run(game);

	delete game;
	delete server;
}
