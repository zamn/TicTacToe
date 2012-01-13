#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string>
#include <cstdio>
#include "ProtocolHandler.h"
#include <cstring>

using namespace std;

int ProtocolHandler::interpret(char buffer[]) {
	cout << "hi" << endl;	
	int size = (buffer[0] >> 4);
	int command = (buffer[0] & ~240);
	char symbol = buffer[1];
	cout << symbol << endl;
	return 0;
}
