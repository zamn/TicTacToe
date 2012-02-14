#include <iostream>
#include <cstring>
#include "Socket.h"
#include "ProtocolHandler.h"
#include "Game.h"
#include "GameManager.h"
#include "Player.h"

using namespace std;

/* 
 * Handle Intial Connection - handleInit(fd)
 * This method handles the initial connectiong making sure
 * that the user is sending a CONNECT message rather than
 * taking up a file descriptor for nothing! :)
 *
 */


Player* Socket::handleInit(int fd) {
	char buf[1024];
	memset(buf, '\0', 1024);
	int len = 1024;
	int con = 0; 
	con = recv(fd, buf, len, 0);

	if (ph->interpret(buf) == 1) {
		int size = (buf[0] >> 4);
		int command = (buf[0] & ~240);
		char symbol = buf[1];
		string user;
		for (int i = 2; i < size+2; i++) {
			user += buf[i];
		}
		cout << "User: " <<  user << endl;
		cout << "Symbol: " << symbol << endl;
		ph->sendSuccess(fd);
		return new Player(fd, user, symbol);
	}

	return NULL; 
}

/*
 * Determine Choice - detChoice(fd)
 * This method determines what the person wants to do. Depending
 * on their choice is what objects are created. 
 *
 * 3 == Create a new game
 * 2 == Join a game
 * -1 == connection died.
 *
*/

int Socket::detChoice(int fd) {
	int len = 1024;
	int con = 0;
	int gameID;
	char buf[1024];
	memset(buf, '\0', 1024);
	char* msg;

	recv(fd, buf, len, 0); 
	if (ph->interpret(buf) == 3) {
		return 3;
	}

	return -1;
	
}
