#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "ProtocolHandler.h"
#include "User.h"

int interpFail(char*);

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
	send(fd, sendBuffer, 1024, 0);
	recv(fd, sendBuffer, 1024, 0);
	return (int)sendBuffer[0];
}

int ProtocolHandler::create(int* gid) {
	char* sendBuffer = new char[10];
	sendBuffer[0] = (char)3;
	send(fd, sendBuffer, 10, 0);
	recv(fd, sendBuffer, 10, 0);
	if ((int)sendBuffer[0] == 2) {
		*gid = sendBuffer[1];
	}
	return (int)sendBuffer[0];
}

int ProtocolHandler::joinGame(int gid) {
 	char* sendBuffer = new char[10];
	memset(sendBuffer, '\0', 10);
	sendBuffer[0] = (char)4;
	sendBuffer[1] = (char)gid;
	send(fd, sendBuffer, 10, 0);
	recv(fd, sendBuffer, 10, 0);
	if ((int)sendBuffer[0] != 2) {
		return interpFail(sendBuffer);
	}
	else
		return (int)sendBuffer[0];
}

void ProtocolHandler::sendNick(std::string nick) {
	char* sendBuffer = new char[13];
	sendBuffer[0] = ((nick.length() << 4) | 8);
	strncpy(sendBuffer + 1, nick.c_str(), nick.length());
	send(fd, sendBuffer, 13, 0);
}

void ProtocolHandler::sendSymbol(char symbol) {
	char* sendBuffer = new char[2];
	sendBuffer[0] = (char)9;
	sendBuffer[1] = symbol;
	send(fd, sendBuffer, 13, 0);
}

bool ProtocolHandler::getOpponent(User* p2) {
	cout << "getting opponent here.. i wonder whats happneing behind th scenes! :D " << endl;
	char* recvBuffer = new char[20];
	memset(recvBuffer, NULL, 20);
	if (recv(fd, recvBuffer, 20, 0) != -1) {
		cout << "am i getting the information?" << endl;
		if ((recvBuffer[0] & 15) == 1) {
			p2->setSymbol(recvBuffer[1]);
			string temp;
			int len = (recvBuffer[0] >> 4);
			for (int i = 2; i < len+2; i++) {
				temp += recvBuffer[i];
			}
			p2->setNick(temp);
			return true;
		}
	}
	delete[] recvBuffer;
	cout << "I should not be getting here!!!!!!!!!!!!" << sizeof(recvBuffer) << endl;
	return false;
}

void ProtocolHandler::sendMove(int move) {
	char* sendBuffer = new char[2];
	sendBuffer[0] = (char)((move << 4) | 5);
	send(fd, sendBuffer, 10, 0);
}

int ProtocolHandler::getMove() {
	char* recvBuffer = new char[10];
	recv(fd, recvBuffer, 10, 0);
	int message = recvBuffer[0] & ~240;
	int failCode = interpFail(recvBuffer);
	if ((message == 7) && (failCode == 6)) {
		return -1;
	}
	return ((recvBuffer[0] & 240) >> 4);
}

// Sends the decision to replay the game or not to opponent
// Then receives the opponents decision and returns that
// If opponent sends it in the wrong format this returns -1
int ProtocolHandler::sendReplay(int decision) {
	char* sendBuffer = new char[10];
	cout << "Decision: " << decision << endl;
	sendBuffer[0] = (decision << 4);
	sendBuffer[0] |=  11;
	send(fd, sendBuffer, 1, 0);
	memset(sendBuffer, NULL, 10);
	recv(fd, sendBuffer, 10, 0);
	cout << "am i getting here?" << endl;
	cout << "sendbuffer[0]  " << (int)(sendBuffer[0] & 15) << endl;
	if ((sendBuffer[0] & ~240) == 11) {
		return ((sendBuffer[0] & 240) >> 4);
	}
	return -1;
}

int interpFail(char* buf) {
	buf[0] &= 240;
	return (buf[0] >> 4);
}
