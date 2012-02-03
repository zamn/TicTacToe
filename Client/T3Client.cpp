#include <iostream>
#include <string.h>
#include <sys/types.h> // for socket()
#include <sys/socket.h> // for socket()
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

int main(void) {
	cout << "Welcome to TicTacToe Online Multiplayer!" << endl;
	cout << "Please enter a server ip (IPv4):" << endl;
	struct addrinfo hints, *res;
	int sockfd;
	int con = 0;
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	string ip;
	cin >> ip;
	getaddrinfo(ip.c_str(), "6000", &hints, &res);
	sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	cout << ip << endl;
	while ((con = connect(sockfd, res->ai_addr, res->ai_addrlen)) != 0)  {
		cout << "Error with server IP " << ip << ". Please try again: " << endl;	
		cin >> ip;
	}
	return 0;
}
