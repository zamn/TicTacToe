#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string>
#include <cstdio>
#include "ProtocolHandler.h"
#include <cstring>

using namespace std;

int getSize(char* arr) {
	int count = 0;
	while (*(arr + count) != '\0') {
		count++;
	}
	return count;
}

int ProtocolHandler::interpret(char* buffer) {
	int size = (buffer[0] >> 4);
	int command = (buffer[0] & ~240);
	char symbol = buffer[1];
	if (command == 1) {
		if (getSize(buffer) >= 3) {
			return 1;
		}
	}
	else if (command == 3) {
		return 3;
	}
	else if (command == 4) {
		if (getSize(buffer) >= 2) {
			return 4;
		}
	}
	return 0;
}
