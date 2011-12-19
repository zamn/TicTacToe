#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include "ProtocolHandler.h"

using namespace std;

int ProtocolHandler::intPlayer(int fd) {
	char buf[1024];
	memset(buf, 0, 1024);
	int len = 500;

	con = recv(fd, buf, len, 0);
	cout << buf << endl;
	return 1;
}
