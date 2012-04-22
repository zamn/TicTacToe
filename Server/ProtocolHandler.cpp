#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string>
#include <cstdio>
#include <cstring>
#include "ProtocolHandler.h"
#include "GameManager.h"

using namespace std;

int getSize(unsigned char* arr) {
	int count = 0;
	while (*(arr + count) != '\0') {
		count++;
	}
	return count;
}

int ProtocolHandler::interpret(unsigned char* buffer) {
	int command = (buffer[0] & ~240);
	if (command == 1) {
		if (getSize(buffer) >= 3) {
			return 1;
		}
	}
	else if (command == 5) {
		return 5;
	}
	else if (command == 6) {
		return 6;
	}
	else if (command == 8) {
		if (getSize(buffer) >= 2) {
			return 8;
		}
	}
	command = buffer[0];
	if (command == 3) {
		return 3;
	}
	else if (command == 4) {
		if (getSize(buffer) == 2) {
			return 4;
		}
	}
	else if (command == 9) {
		if (getSize(buffer) == 2) {
			return 9;
		}
	}
	return -1;
}

/*
 * Send Failure!
 * --> 1 == Invalid Game ID.
 * --> 5 == Game already full!
*/

void ProtocolHandler::sendFail(int fd, int reason) {
	char* msg = new char[10];
	memset(msg, '\0', 10);
	msg[0] = ((reason << 4) | 7);
	send(fd, msg, 1, 0);
	delete[] msg;
}

void ProtocolHandler::sendSuccess(int fd, int gid) {
	char* msg = new char[10];
	memset(msg, '\0', 10);
	msg[0] = (char)2;
	msg[1] = (char)gid;
	send(fd, msg, 2, 0);
	delete[] msg;
}

void ProtocolHandler::sendSuccess(int fd) {
	char* msg = new char[10];
	memset(msg, '\0', 10);
	msg[0] = (char)2;
	int len = 1;
	send(fd, msg, len, 0);
	delete[] msg;
}

void ProtocolHandler::sendInfo(Game* g) {
	char* sendBuffer = new char[20];
	memset(sendBuffer, '\0', 20);
	Player** players = g->getPlayers();
	string temp;
	for (int i = 0; i < 2; i++) {
		sendBuffer[0] = ((players[i]->getNick().length() << 4) | 1);
		sendBuffer[1] =  players[i]->getSymbol();
		for (unsigned int j = 0; j < players[i]->getNick().length(); j++) {
			temp += players[i]->getNick()[j];
		}
		strncpy(sendBuffer + 2, temp.c_str(), temp.length());
		cout << "Temp for : " << i << " is: " << temp << endl;
		cout << "Symbol for: " << i << " is: " << sendBuffer[1] << endl;
		if (i == 0)
			send(players[i+1]->getFD(), sendBuffer, 20, 0); 
		else
			send(players[i-1]->getFD(), sendBuffer, 20, 0); 
		temp = "";
	}
	delete[] sendBuffer;
}

void ProtocolHandler::sendMove(Player* p, int move) {
	char* sendBuffer = new char[20];
	memset(sendBuffer, '\0', 20);
	sendBuffer[0] = ((move << 4) | 5);
	cout << "sending to: " << p->getNick() << " pos: " << move << endl;
	send(p->getFD(), sendBuffer, 1, 0);
	delete[] sendBuffer;
}

void ProtocolHandler::listPlayers(int fd, GameManager* gm) { 
	int totalGames = 13 * gm->getLength();
	char* sendBuffer = new char[totalGames];
	int count = 0;
	for (int i = 0; i < gm->getLength(); i++) {
		if (gm->exists(i)) {
			Game* g = gm->getGame(i);
			int nickLen = g->getOwner().size();
			sendBuffer[count] = nickLen << 4;
			if (g->isFull())
				sendBuffer[count] |= 1;
			count++;
			sendBuffer[count] = i+1;
			count++;
			for (int j = 0; j < nickLen; j++) {
				sendBuffer[count] = g->getOwner()[j];
				count++;
			}
		}
	}
	send(fd, sendBuffer, totalGames, 0);
	delete[] sendBuffer;
}
