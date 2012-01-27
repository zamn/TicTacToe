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
		cout << *(arr + count) << endl;
		count++;
	}
	cout << count << endl;
	return 0;
}

int ProtocolHandler::interpret(char* buffer) {
	int size = (buffer[0] >> 4);
	int command = (buffer[0] & ~240);
	char symbol = buffer[1];
	if (command == 1) {
		if (getSize(buffer) >= 3) {
		}
	}
	else if (command == 3) {
	}
	return 0;
}
