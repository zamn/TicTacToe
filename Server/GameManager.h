#ifndef _GAMEMANAGER_H
#define _GAMEMANAGER_H
#include <stack>
#include "Game.h"
#include "Player.h"

class GameManager {
	public:
		GameManager();
		bool exists(int);
		int addGame(Game*);
		Game* getGame(int);
		bool removeGame(int);
		int getLength();
	private:
		int tracker;
		static const int maxGameCount = 31;
		stack<int> *free;
		Game* games[maxGameCount];
};
#endif
