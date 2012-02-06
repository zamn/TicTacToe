#include <iostream>
#include <string.h>
#include <sys/types.h> // for socket()
#include <sys/socket.h> // for socket()
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdlib> // for system

using namespace std;

int main(void) {
	struct addrinfo hints, *res;
	struct sockaddr_in sa;
	struct hostent *he;
	char* dest[32];
	int sockfd;
	int con = 0;
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;

	system("clear");
	cout << "Welcome to TicTacToe Online Multiplayer!" << endl;
	cout << "Please enter a server ip (IPv4):" << endl;
	string ip;
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

	//recv(
	return 0;
}
