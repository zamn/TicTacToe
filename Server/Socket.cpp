#include <iostream>
#include "Socket.h"
#include "ProtocolHandler.h"

using namespace std;

int Socket::handle(int fd) {
	char buf[1024];
	ProtocolHandler ph;
	int len = 500;
	int con = 0; 
	while (true) {
		con = recv(fd, buf, len, 0);
	}
	ph.interpret(buf);

	return 1337;
}
