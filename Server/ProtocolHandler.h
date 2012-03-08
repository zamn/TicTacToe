#ifndef _PROTOCOLHANDLER_H
#define _PROTOCOLHANDLER_H
#include <iostream>
#include <sys/socket.h>
#include "Game.h"
#include "Player.h"

using namespace std;

class ProtocolHandler {
	public:
		int interpret(unsigned char*);
		void sendMove(Player*, int);
		void sendFail(int, int);
		void sendSuccess(int, int);
		void sendSuccess(int);
		void sendInfo(Game*);
};
#endif
