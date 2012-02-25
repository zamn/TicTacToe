#ifndef _PROTOCOLHANDLER_H
#define _PROTOCOLHANDLER_H

class ProtocolHandler {
	public:
		ProtocolHandler(int);
		int sendInfo(std::string, char);
		int create(int*);
		int joinGame(int);
		void sendNick(std::string);
		void sendSymbol(char);
	private:
		int fd;
};
#endif
