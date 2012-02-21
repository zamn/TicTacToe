#include <iostream>
#include <string.h>
#include <sys/types.h> // for socket()
#include <sys/socket.h> // for socket()
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdio> // for fgets
#include <cstdlib> // for system
#include "GameBoard.h"
#include "User.h"
#include "ProtocolHandler.h"

using namespace std;

User* player;
User* player2;
GameBoard* gb;
ProtocolHandler* ph;
void play(int);

int main(void) {
	struct addrinfo hints, *res;
	struct hostent *he;
	string ip;
	string username;
	char symbol;
	int sockfd;
	int option = 0;
	int con = 0;
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;

	system("clear");
	cout << "Welcome to TicTacToe Online Multiplayer!" << endl;
	cout << "Please enter a server ip (IPv4):" << endl;
	cin >> ip;
	he = gethostbyname(ip.c_str());
	while ((he = gethostbyname(ip.c_str())) == 0) {
		cout << "Not a valid IPv4 Address!" << endl;
		cout << "Please enter a server ip (IPv4): " << endl;
		cin >> ip;
	}
	getaddrinfo(ip.c_str(), "6000", &hints, &res);
	sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

	while ((con = connect(sockfd, res->ai_addr, res->ai_addrlen)) != 0)  {
		cout << "Error with server IP " << ip << ". Please try again: " << endl;	
		cin >> ip;
		getaddrinfo(ip.c_str(), "6000", &hints, &res);
		sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	}

	ph = new ProtocolHandler(sockfd);
	cout << "Successfully connected to server!" << endl;
	cout << "Please enter your username (Max 12 char): " << endl;
	cin >> username;
	username = username.substr(0, 13);
	cout << "Please enter your symbol: " << endl;
	cin >> symbol;

	
	if (ph->sendInfo(username, symbol) == 2) {
		player = new User(username, symbol);
		player2 = new User("????", '?');
		system("clear");
		cout << "Your username is set to: " << username << endl;
		cout << "Your symbol is set to: " << symbol << endl;
		cout << "Please select an option from the following menu: " << endl;
		cout << "1. Create a new game" << endl;
		cout << "2. Join a game" << endl;
		cout << "3. exit " << endl;
		cout << "\n=> ";
		cin >> option;
	}
	else {
		cout << "Failed to join game!" << endl;
	}

	switch(option) {
		int gid;
		case 1:
			if (ph->create(&gid) == 2) {
				gb = new GameBoard(player, player2);
				play(gid);
			}
			break;
		case 2:
			cout << "Please enter the Game ID: ";
			cin >> gid;

			if (ph->joinGame(gid) == 2) {
				cout << "Successfully joined the game!" << endl;
			}
			break;
	}
	
	return 0;
}

void play(int gid) {
	system("clear");
	cout << "Game created! Game ID: " << (100 + gid) << endl;
	int move;
	cout << "Waiting on an opponent to join...\n";
	while (!gb->gameOver(player2->getNick())) {
		gb->draw();
		cout << "Please enter the spot number where you want to move: ";
		cin >> move;
	}
}
