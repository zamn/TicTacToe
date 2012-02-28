#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string>
#include <cstdio>
#include "ProtocolHandler.h"
#include <cstring>

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
	char* msg = new char[1];
	msg[0] = ((reason << 4) | 7);
	send(fd, msg, 10, 0);
}

void ProtocolHandler::sendSuccess(int fd, int gid) {
	char* msg = new char[1];
	msg[0] = (char)2;
	msg[1] = (char)gid;
	send(fd, msg, 10, 0);
}

void ProtocolHandler::sendSuccess(int fd) {
	char* msg = new char[1];
	msg[0] = (char)2;
	int len = 10;
	send(fd, msg, len, 0);
}

void ProtocolHandler::sendInfo(Game* g) {
	char* sendBuffer = new char[20];
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
}
