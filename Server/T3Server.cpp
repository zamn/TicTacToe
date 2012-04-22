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
#include "T3Choices.cpp"

using namespace std;

GameManager gm;
ProtocolHandler ph;

void *handleCon(void* arg) {
	Socket sh;
	int fd = (unsigned long)arg;
	Player* p1;
	cout << "A new connection has come up!" << endl;
	int choice;
	if ((p1 = sh.handleInit(fd)) != 0) {
		int gameID = -1;
	       	while ((choice = sh.detChoice(fd, &gameID)) != -1) {
			cout << choice << endl;
			if (choice == CREATE_GAME) {
				if ((gameID = gm.addGame(new Game(p1))) != -1) {
					std::cout << "gamied: " << gameID << endl;
					std::cout << "New game has been created!" << endl;
					ph.sendSuccess(fd, gameID+1);
					p1->setGID(gameID);
				}
				else {
					ph.sendFail(fd, 7);
				}
			}
			else if (choice == JOIN_GAME) {
				cout << "Connection has chosen 2." << endl;
				Game* g;
				if ((g = gm.getGame(gameID-1)) != '\0') {
					int result;
					if ((result = g->addPlayer(p1)) == 0) {
						cout << "Successfully added to game: " << gameID << endl ;
						ph.sendSuccess(fd);
						ph.sendInfo(g);
						p1->setGID(gameID-1);
					}
					else if (result == 3) {
						cout << "Invalid symbol!" << endl;
						ph.sendFail(fd, 3);
					}
					else if (result == 4) {
						cout << "Same nick! BAD!" << endl;
						ph.sendFail(fd, 4);
					}
					else if (result == 5)  {
						if (g->exists(p1)) { 
							ph.sendInfo(g);
						}
						else {
							cout << "Game is full " << endl;
							ph.sendFail(fd, 5);
						}
					}
				}
				else {
					cout << "Invalid Game ID!" << endl;
					ph.sendFail(fd, 1);
				}
			}
			else if (choice == SEND_MOVE) {
				Player* player = gm.getGame(p1->getGID())->getOpposite(p1);
				ph.sendMove(player, gameID);
			}
			else if (choice == CHANGE_NICK) {
				string nick = sh.getNick();
				if (!nick.empty())
					p1->setNick(nick);
				cout << "Changed persons name to: " << nick << endl;
			}
			else if (choice == CHANGE_SYMBOL) {
				char sym = sh.getSymbol();
				if (sym != ' ') {
					p1->setSymbol(sym);
				}
				cout << "Changed persons symbol to: " << sym << endl;
			}
			else if (choice == LIST) {
				ph.listPlayers(fd, &gm);
			}
			else if (choice == LEAVE) {
				if (p1->getGID() != -1) {
					Player* player = gm.getGame(p1->getGID())->getOpposite(p1);
					gm.getGame(p1->getGID())->removePlayer(p1);
					ph.sendFail(player->getGID(), 6);
				}
				// on rejoin dont remove game, just remove player
				// then re-add player with same game id
			}
			else {
				ph.sendFail(fd, 0);
			}
		}
	}
	if ((p1 != NULL) && (p1->getGID() != -1) && (gm.getGame(p1->getGID())->isFull())) {
		Player* player = gm.getGame(p1->getGID())->getOpposite(p1);
		int gid = p1->getGID();
		gm.getGame(gid)->removePlayer(p1);
		ph.sendFail(player->getFD(), 6);
		gm.removeGame(gid);
		cout << "Player has quit!" << endl;
	}
	cout << "HE QUIT! " << choice <<  endl;
	// implement deleting stuff here...
	// push game on to stack once its done
	close(fd);
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
