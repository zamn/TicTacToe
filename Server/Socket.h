#ifndef _SOCKET_H
#define _SOCKET_H
#include <iostream>
#include <sys/socket.h>
#include "Player.h"
#include "GameManager.h"

using namespace std;

class Socket {
	public:
		Socket();
		int handleInit(int);
		int detChoice(int);
	private:
		Player* p1;
		Player* p2;
		GameManager* gm;
		Game* game;
};
#endif
