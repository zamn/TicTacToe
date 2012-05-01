#include <iostream>
#include <cstring>
#include <cctype>
#include "Game.h"
#include "Player.h"

string tolower(string);

Game::Game(Player* p1) {
	this->p1 = p1;
	this->p2 = p2;
	pcount = 1;
}

Game::~Game() {
	if (p2 != NULL) {
		delete p2;
	}
}

Player* Game::getOwner() {
	return p1;
}

// Sends the specified move from the specified player
// As long as the game is full we assume its preceding 
// and thats when we send the move.
// Otherwise, return false!
bool Game::sendMove(string origin, int pos) {
	if (isFull()) {
		if (p1->getNick().compare(origin))
			send(p2->getFD(), origin.c_str(), origin.length(), 0);
		else
			send(p1->getFD(), origin.c_str(), origin.length(), 0);
		return true;
	}
	else
		return false;
}

// Adds a player to the game
// Returns 4 if nicknames are the same
// Returns 3 if the symbols are the same
// Returns 0 on success
// Returns 5 if the game is full1
int Game::addPlayer(Player* player) {
	cout << "am i even getting inside this?" << endl;
	if (!isFull()) {
		if (tolower(p1->getNick()).compare(tolower(player->getNick())) == 0) {
			return 4;
		}
		else if (std::tolower(p1->getSymbol()) == (std::tolower(player->getSymbol()))) {
			return 3;
		}
		else {
			if (p1 != NULL)
				this->p2 = player;
			else
				this->p1 = player;
			pcount++;
			std::cout << "Game is now full!" << endl;
			return 0;
		}
	}
	else 
		return 5;
}

// Removes the specified player from the game
int Game::removePlayer(Player* player) {
	if (player == p1) { 
		rdFD = p1->getFD();
		p1 = NULL;
		p1 = p2;
		p2 = NULL;
	}
	else {
		rdFD = p2->getFD();
		p2 = NULL;
	}
	pcount--;
	return pcount;
}

int Game::recentFD() {
	return rdFD;
}

// Returns either all players or a single player
Player** Game::getPlayers() {
	Player** temp = new Player*[2];
	if (isFull())  {
		temp[0] = p1;
		temp[1] = p2;
	}
	else
		temp[0] = p1;
	return temp;
}

// Precondition: Player MUST be in the game! otherwise this will return player1 always
Player* Game::getOpposite(Player* player) {
	if (player->getSymbol() == p1->getSymbol()) {
		return p2;
	}
	else {
		return p1;
	}
}

bool Game::exists(Player* player) {
	if (p2->getFD() == player->getFD()) {
		return true;
	}
	return false;
}

bool Game::isFull() {
	if (pcount == 2)
		return true;
	else
		return false;
}

// Reinventing the wheel
string tolower(string str) {
	string temp = "";
	for (unsigned int i = 0; i < str.length(); i++) {
		temp += std::tolower(str[i]);
	}
	return temp;
}
