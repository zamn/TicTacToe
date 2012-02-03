#include <iostream>
#include <cstring>
#include "Socket.h"
#include "ProtocolHandler.h"

using namespace std;

int Socket::handleInit(int fd) {
	char buf[1024];
	memset(buf, '\0', 1024);
	ProtocolHandler ph;
	int len = 1024;
	int con = 0; 
	con = recv(fd, buf, len, 0);

	if (ph.interpret(buf) == 1) {
		cout << "i\'s here?" << endl;
		char* msg = new char[1];
		msg[0] = (char)2;
		len = 10;
		cout << msg << endl;
		send(fd, msg, len, 0);
	}

	return ph.interpret(buf);
}

int Socket::handle(int fd) {
	
}
