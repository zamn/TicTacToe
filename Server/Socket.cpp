#include <iostream>
#include <cstring>
#include "Socket.h"
#include "ProtocolHandler.h"

using namespace std;

int Socket::handle(int fd) {
	char buf[1024];
	memset(buf, '\0', 1024);
	ProtocolHandler ph;
	int len = 500;
	int con = 0; 
	con = recv(fd, buf, len, 0);
	ph.interpret(buf);

	return 1337;
}
