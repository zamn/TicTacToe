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

Socket::Socket() {
	gm = new GameManager();
}

int Socket::handleInit(int fd) {
	char buf[1024];
	memset(buf, '\0', 1024);
	ProtocolHandler ph;
	int len = 1024;
	int con = 0; 
	con = recv(fd, buf, len, 0);

	if (ph.interpret(buf) == 1) {
		int size = (buf[0] >> 4);
		int command = (buf[0] & ~240);
		char symbol = buf[1];
		string user;
		for (int i = 2; i < size+2; i++) {
			user += buf[i];
		}
		p1 = new Player(fd, user, symbol);
		cout << "User: " <<  user << endl;
		cout << "Symbol: " << symbol << endl;
		cout << "i\'s here?" << endl;
		char* msg = new char[1];
		msg[0] = (char)2;
		len = 10;
		send(fd, msg, len, 0);
	}

	return ph.interpret(buf);
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
	ProtocolHandler ph;	
	int len = 1024;
	int con = 0;
	char buf[1024];
	memset(buf, '\0', 1024);
	char* msg;

	recv(fd, buf, len, 0); 
	if (ph.interpret(buf) == 3) {
		msg = new char[2];
		msg[0] = (char)2;
		game = new Game(p1);
		gm->addGame(game);
		Game* garr = gm->getGame(0);
		Player** parr = garr->getPlayers();
		cout << parr[0]->getNick() << endl;
		// Work on send back message.
		return 3;
	}

	return -1;
	
}
