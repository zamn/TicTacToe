#ifndef _PROTOCOLHANDLER_H
#define _PROTOCOLHANDLER_H
#include <iostream>
#include <sys/socket.h>

using namespace std;

class ProtocolHandler {
	public:
		int interpret(char[]);
};
#endif
