#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string>
#include <cstdio>
#include "ProtocolHandler.h"
#include <cstring>

using namespace std;


int wordCount(string str) {
	int words = 1;
	for (const char* s = str.c_str(); *s; s++) if (*s == ' ') words++;
	return words;
}

/* intPlayer Return Values
 * -2 == invalid string
 * -1 == not enough parameters
 *  1 == JOIN a game
 *  2 == CREATE a game
 *  3 == Make a MOVE
 */

int ProtocolHandler::intPlayer(int fd) {
	char buf[1024];
	int len = 500;
	int con = recv(fd, buf, len, 0);
	string msg = buf;
	string fword = msg.substr(0, msg.find_first_of(" "));
	if (wordCount(msg) < 4)
		return -1;
	else if (fword.compare("JOIN"))
		return 1;
	else if (fword.compare("CREATE"))
		return 2;
	else if (fword.compare("MOVE"))
		return 3;
	return -2;
}

