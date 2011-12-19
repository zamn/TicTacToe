#include <iostream>
#include "Player.h"

using namespace std;

Player::Player(sockaddr_storage ip, int clientID, int gameID, string nick, char symbol) {
	addr = ip;
	this->clientID = clientID;
	this->nick = nick;
	this->symbol = symbol;
}

int Player::getGameID() {
	return gameID;
}

char Player::getSymbol() {
	return symbol;
}

string Player::getNick() {
	return nick;
}

int Player::getClientID() {
	return clientID;
}

void Player::setGameID(int id) {
	gameID = id;
}
