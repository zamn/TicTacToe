#include <iostream>
#include <string.h>
#include <sys/types.h> // for socket()
#include <sys/socket.h> // for socket()
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdio> // for fgets
#include <cstdlib> // for system

using namespace std;

int main(void) {
	struct addrinfo hints, *res;
	struct sockaddr_in sa;
	struct hostent *he;
	char* dest[32];
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

	cout << "Successfully connected to server!" << endl;
	cout << "Please enter your username (Max 12 char): " << endl;
	cin >> username;
	username = username.substr(0, 13);
	cout << "Please enter your symbol: " << endl;
	cin >> symbol;

	char* sendBuffer = new char[1024];
	char* recBuffer = new char[1024];

	sendBuffer[0] = (char)((username.length() << 4) | 1);
	sendBuffer[1] = symbol;

	strncpy(sendBuffer + 2, username.c_str(), username.length());
	send(sockfd, sendBuffer, 1024, NULL);
	memset(sendBuffer, '\0', 1024);
	recv(sockfd, recBuffer, 1024, NULL);
	if ((int)recBuffer[0] == 2) {
		system("clear");
		cout << "Your username is set to: " << username << endl;
		cout << "Your symbol is set to: " << symbol << endl;
		cout << "Please select an option from the following menu: " << endl;
		while (option != 3) {
			cout << "1. Create a new game" << endl;
			cout << "2. Join a game" << endl;
			cout << "3. exit " << endl;
			cout << "\n=> ";
			cin >> option;

			switch(option) {
				case 1:
					sendBuffer[0] = (char)3;
					send(sockfd, sendBuffer, 10240, NULL);
					break;
				case 2:
					cout << "You chose choice 2" << endl;
					break;
			}
		}
	}
	else {
		cout << "Failed to join game!" << endl;
	}
	//recv(
	return 0;
}
