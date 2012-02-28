#ifndef _PROTOCOLHANDLER_H
#define _PROTOCOLHANDLER_H
#include "User.h"

class ProtocolHandler {
	public:
		ProtocolHandler(int);
		int sendInfo(std::string, char);
		int create(int*);
		int joinGame(int);
		void sendNick(std::string);
		void sendSymbol(char);
		bool getOpponent(User*);
		void sendMove(int);
	private:
		int fd;
};
#endif
