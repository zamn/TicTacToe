#ifndef _SOCKET_H
#define _SOCKET_H
#include <iostream>
#include <sys/socket.h>
#include "Player.h"
#include "ProtocolHandler.h"

using namespace std;

class Socket {
	public:
		Player* handleInit(int);
		int detChoice(int, int*);
		string getNick();
		char getSymbol();
	private:
		ProtocolHandler* ph;
		string temp;
};
#endif
