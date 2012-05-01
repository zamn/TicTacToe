#ifndef _PROTOCOLHANDLER_H
#define _PROTOCOLHANDLER_H
#include <iostream>
#include <sys/socket.h>
#include "Game.h"
#include "Player.h"
#include "GameManager.h"

using namespace std;

class ProtocolHandler {
	public:
		int interpret(unsigned char*);
		void sendMove(Player*, int);
		void sendMove(int, int);
		void sendFail(int, int);
		void sendSuccess(int, int);
		void sendSuccess(int);
		void sendReplay(int, int);
		void sendInfo(Game*);
		void listPlayers(int, GameManager*);
};
#endif
