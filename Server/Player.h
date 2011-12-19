#ifndef _PLAYER_H
#define _PLAYER_H
#include <iostream>
#include <sys/socket.h>

using namespace std;

class Player {
	public:
		Player(sockaddr_storage, int, int, string, char);
		int getGameID();
		char getSymbol();
		string getNick();	
		int getClientID();
		void setGameID(int);
	private:
		struct sockaddr_storage addr;
		int clientID;
		string nick;
		char symbol;
		int gameID;
};
#endif
