#ifndef _GAMEMANAGER_H
#define _GAMEMANAGER_H
#include "Game.h"
#include "Player.h"

using namespace std;

class GameManager {
	public:
		exists(int);
		addGame(Game);
	private:
		vector<Game> games;
};
