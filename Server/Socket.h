#ifndef _SOCKET_H
#define _SOCKET_H
#include <iostream>
#include <sys/socket.h>

using namespace std;

class Socket {
	public:
		int handleInit(int);
		int handle(int);
};
#endif
