#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>
#include "ProtocolHandler.h"

using namespace std;

int ProtocolHandler::intPlayer(int fd) {
	char buf[1024];
	memset(buf, 0, 1024);
	int len = 500;

	int con = recv(fd, buf, len, 0);
	cout << "diz b called?" << endl;
	cout << buf << endl;
	return 1;
}
