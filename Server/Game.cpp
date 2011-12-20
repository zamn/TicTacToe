#include "Game.h"
#include "Player.h"

Game::Game(Player *p1) {
	this->p1 = p1;
}

void Game::sendMove(string origin, int pos) {
	// tell other player origin's move
}

bool Game::addPlayer(Player *p2) {
	if (!full) {
		this->p2 = p2;
		full = true;
	}
	else
		return false;

	return true;
}
