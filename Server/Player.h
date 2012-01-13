#ifndef _PLAYER_H
#define _PLAYER_H
#include <iostream>
#include <sys/socket.h>

using namespace std;

class Player {
	public:
		Player(int, string, char);
		char getSymbol();
		string getNick();	
		int getFD();
	private:
		int fd;
		string nick;
		char symbol;
};
#endif
