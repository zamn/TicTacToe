#include <iostream>
#include <cstring>
#include <cctype>
#include "Game.h"
#include "Player.h"

string tolower(string);

Game::Game(Player *p1) {
	this->p1 = p1;
}

Game::~Game() {
	delete p1;
	delete p2;
}

// Sends the specified move from the specified player
// As long as the game is full we assume its preceding 
// and thats when we send the move.
// Otherwise, return false!
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

// Adds a player to the game
// Returns 4 if nicknames are the same
// Returns 3 if the symbols are the same
// Returns 0 on success
// Returns 5 if the game is full1
int Game::addPlayer(Player* player) {
	if (!full) {
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
			full = true;
			std::cout << "Game is now full!" << endl;
			return 0;
		}
	}
	else 
		return 5;
}

// Removes the specified player from the game
bool Game::removePlayer(Player* player) {
	if (player == p1) { 
		delete p1;
	}
	else {
		delete p2;
	}
	full = false;
	return full;
}

// Returns either all players or a single player
Player** Game::getPlayers() {
	Player** temp = new Player*[2];
	if (full)  {
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

// Reinventing the wheel
string tolower(string str) {
	string temp = "";
	for (unsigned int i = 0; i < str.length(); i++) {
		temp += std::tolower(str[i]);
	}
	return temp;
}
