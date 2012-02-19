#include <iostream>
#include <pthread.h>
#include <errno.h> // debugging
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include "Socket.h"
#include "GameManager.h"
#include "Player.h"
#include "Game.h"
#include "ProtocolHandler.h"

using namespace std;

GameManager gm;

void *handleCon(void* arg) {
	Socket sh;
	int fd = (unsigned long)arg;
	Player* p1;
	cout << "A new connection has come up!" << endl;
	if ((p1 = sh.handleInit(fd)) != NULL) {
		if (sh.detChoice(fd) == 3) {
			int gameID;
			if ((gameID = gm.addGame(new Game(p1))) != -1) {
				Game* g1 = gm.getGame(gameID);
				Player** parr = g1->getPlayers();
				cout << parr[0]->getNick() << endl;
				ProtocolHandler ph;
				ph.sendSuccess(gameID, fd);
			}
		}
	}
	cout << "HE QUIT! " << endl;
	return 0;
}

int main(void) {

	struct addrinfo hints;
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC; // use ipv4 or ipv6
	hints.ai_socktype = SOCK_STREAM; // tcp
	hints.ai_flags = AI_PASSIVE; // fill in ip

	struct addrinfo *res;

	int status;
	if ((status = getaddrinfo(NULL, "6000", &hints, &res)) != 0) {
		fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
		return 1;
	}

	int sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	if (sock == -1) {
		cout << "error with socket :x" << endl;
	}

	int bnd = bind(sock, res->ai_addr, res->ai_addrlen);
	if (bnd == -1) {
		cout << "error with bind!" << endl;
	}

	int listener = listen(sock, 20); // listening!
	if (listener == -1) {
		cout << "error with listener" << endl;
	}

	socklen_t addr_size;
	struct sockaddr_storage their_addr;
	addr_size = sizeof their_addr;
	int new_fd;
	while (true) {
		new_fd = accept(sock, (struct sockaddr *)&their_addr, &addr_size);
		if (new_fd) {
			pthread_t tid;
			int ret;
			if ((ret = pthread_create(&tid, NULL, handleCon, (void*)new_fd)) != 0) {
				cout << "ERROR!" << strerror(ret) << endl;
				exit(1);
			}
		}
	}

	return 0;
}
