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

void Player::setSymbol(char c) {
	symbol = c;
}

void Player::setNick(string str) {
	nick = str;
}

void Player::setGID(int game) {
	cout << "IS SETGID BEING CLALED? " << game << endl;
	gameID = game;
}

int Player::getFD() {
	return fd;
}

int Player::getGID() {
	return gameID;
}
