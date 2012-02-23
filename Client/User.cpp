#include "User.h"

User::User(string nick, char symbol) {
	this->nick = nick;
	this->symbol = symbol;
}

string User::getNick() {
	return nick;
}

char User::getSymbol() {
	return symbol;
}

bool User::isTurn() {
	return turn;
}

void User::setTurn(bool t) {
	turn = t;
}
