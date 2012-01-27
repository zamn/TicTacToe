#ifndef _GAMEMANAGER_H
#define _GAMEMANAGER_H
#include "Game.h"
#include "Player.h"

using namespace std;

class GameManager {
	public:
		GameManager();
		bool exists(int);
		bool addGame(Game);
	private:
		Game *games;
};
#endif
