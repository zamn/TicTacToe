#ifndef _GAME_H
#define _GAME_H
#include "Player.h"

using namespace std;

class Game {
	public:
		Game(Player*);
		bool sendMove(string, int);
		bool addPlayer(Player*);
		int gameID;
		Player** getPlayers();
	private:
		bool full;
		Player *p1;
		Player *p2;
};
#endif
