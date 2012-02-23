#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "ProtocolHandler.h"

int interpFail(unsigned char*);

ProtocolHandler::ProtocolHandler(int fd) {
	this->fd = fd;
}

int getSize(char* arr) {
	int count = 0;
	while (*(arr + count) != '\0') {
		count++;
	}
	return count;
}

int ProtocolHandler::sendInfo(std::string username, char symbol) {
	char* sendBuffer = new char[1024];
	sendBuffer[0] = ((username.length() << 4) | 1);
	sendBuffer[1] = symbol;
	strncpy(sendBuffer + 2, username.c_str(), username.length());
	send(fd, sendBuffer, 1024, NULL);
	recv(fd, sendBuffer, 1024, NULL);
	return (int)sendBuffer[0];
}

int ProtocolHandler::create(int* gid) {
	char* sendBuffer = new char[10];
	sendBuffer[0] = (char)3;
	send(fd, sendBuffer, 10, NULL);
	recv(fd, sendBuffer, 10, NULL);
	if ((int)sendBuffer[0] == 2) {
		*gid = sendBuffer[1];
	}
	return (int)sendBuffer[0];
}

int ProtocolHandler::joinGame(int gid) {
	unsigned char* sendBuffer = new unsigned char[10];
	memset(sendBuffer, '\0', 10);
	sendBuffer[0] = (char)4;
	sendBuffer[1] = (char)gid;
	send(fd, sendBuffer, 10, NULL);
	recv(fd, sendBuffer, 10, NULL);
	if ((int)sendBuffer[0] != 2) {
		return interpFail(sendBuffer);
	}
	else
		return (int)sendBuffer[0];
}

int interpFail(unsigned char* buf) {
	return (buf[0] >> 4);
}
