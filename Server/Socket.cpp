#include <iostream>
#include <cstring>
#include "Socket.h"
#include "ProtocolHandler.h"
#include "Game.h"
#include "GameManager.h"
#include "Player.h"

/* 
 * Handle Intial Connection - handleInit(fd)
 * This method handles the initial connectiong making sure
 * that the user is sending a CONNECT message rather than
 * taking up a file descriptor for nothing! :)
 *
 */


Player* Socket::handleInit(int fd) {
	unsigned char buf[1024];
	memset(buf, '\0', 1024);
	int len = 1024;
	int con = 0; 
	con = recv(fd, buf, len, 0);

	if (ph->interpret(buf) == 1) {
		int size = (buf[0] >> 4);
		char symbol = buf[1];
		string user;
		for (int i = 2; i < size+2; i++) {
			user += buf[i];
		}
		std::cout << "User: " <<  user << std::endl;
		std::cout << "Symbol: " << symbol << std::endl;
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

int Socket::detChoice(int fd, int* gid) {
	int len = 1024;
	unsigned char buf[1024];
	memset(buf, '\0', 1024);

	recv(fd, buf, len, 0); 
	int result = ph->interpret(buf);
	if (result == 3) {
		return 3;
	}
	else if (result == 4) {
		*gid = buf[1];
		return 4;
	}
	else if (result == 5) {
		*gid = ((buf[0] & 240) >> 4); //gid = move here
		cout << "gid here: " << *gid << endl;
		return 5;
	}
	else if (result == 6) {
		return 6;
	}
	else if (result == 8) {
		temp = "";
		int count = (buf[0] >> 4);
		for (int i = 1; i <= count; i++) {
			temp += buf[i];
		}
		return 8;
	}
	else if (result == 9) {
		temp = "";
		temp[0] = buf[1];
		return 9;
	}
	else if (result == 10) {
		return 10;
	}
	else if (result == 11) {
		*gid = ((buf[0] & 240) >> 4);
		return 11;
	}

	return -1;
}

string Socket::getNick() {
	cout << "Sending: " << temp << endl;
	return temp;
}

char Socket::getSymbol() {
	return temp[0];
}
