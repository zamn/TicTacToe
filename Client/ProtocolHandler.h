#ifndef _PROTOCOLHANDLER_H
#define _PROTOCOLHANDLER_H

class ProtocolHandler {
	public:
		ProtocolHandler(int);
		int sendInfo(std::string, char);
		int create(int*);
		int joinGame(int);
	private:
		int fd;
};
#endif
