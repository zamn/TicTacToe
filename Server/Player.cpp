#include <iostream>
#include "Player.h"

using namespace std;

Player::Player(int fd, string nick, char symbol) {
	this->fd = fd;
	this->nick = nick;
	this->symbol = symbol;
}

char Player::getSymbol() {
	return symbol;
}

string Player::getNick() {
	return nick;
}
