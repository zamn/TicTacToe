#include <iostream>
#include <cstring>
#include "Game.h"
#include "Player.h"

Game::Game(Player *p1) {
	this->p1 = p1;
}

bool Game::sendMove(string origin, int pos) {
	if (full) {
		if (p1->getNick().compare(origin))
			send(p2->getFD(), origin.c_str(), origin.length(), 0);
		else
			send(p1->getFD(), origin.c_str(), origin.length(), 0);
		return true;
	}
	else
		return false;
}

bool Game::addPlayer(Player* p2) {
	if (!full) {
		this->p2 = p2;
		full = true;
	}
	else
		return false;

	return true;
}

Player** Game::getPlayers() {
	Player** temp;
	if (!full) 
		temp[0] = p1;
	return temp;
}
