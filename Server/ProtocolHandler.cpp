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
