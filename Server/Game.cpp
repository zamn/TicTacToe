#include <iostream>
#include <cstring>
#include <cctype>
#include "Game.h"
#include "Player.h"

string tolower(string);

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

int Game::addPlayer(Player* p2) {
	if (!full) {
		if (tolower(p1->getNick()).compare(tolower(p2->getNick())) == 0) {
			return 4;
		}
		else if (std::tolower(p1->getSymbol()) == (std::tolower(p2->getSymbol()))) {
			return 3;
		}
		else {
			this->p2 = p2;
			full = true;
			std::cout << "Game is now full!" << endl;
			return 0;
		}
	}
	else 
		return 5;
}

Player** Game::getPlayers() {
	Player** temp = new Player*[2];
	if (full)  {
		temp[0] = p1;
		temp[1] = p2;
	}
	else
		temp[0] = p1;

	std::cout << "testing: " << p1->getNick() << std::endl;
	return temp;
}


string tolower(string str) {
	string temp = "";
	for (unsigned int i = 0; i < str.length(); i++) {
		temp += std::tolower(str[i]);
	}
	return temp;
}
