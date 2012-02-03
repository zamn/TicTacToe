#ifndef _GAMEMANAGER_H
#define _GAMEMANAGER_H
#include <stack>
#include "Game.h"
#include "Player.h"

#define MAX_GAMES 32

class GameManager {
	public:
		GameManager();
		bool exists(int);
		bool addGame(Game*);
	private:
		int tracker;
		stack<int> free;
		Game *games[MAX_GAMES];
};
#endif
