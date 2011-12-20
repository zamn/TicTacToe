#ifndef _GAME_H
#define _GAME_H
#include "Player.h"

using namespace std;

class Game {
	public:
		Game(Player*);
		void sendMove(string, int);
		bool addPlayer(Player*);
	private:
		int gameID;
		bool full;
		Player *p1;
		Player *p2;
};
#endif
