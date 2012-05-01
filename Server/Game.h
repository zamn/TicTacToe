#ifndef _GAME_H
#define _GAME_H
#include "Player.h"

using namespace std;

class Game {
	public:
		Game(Player*);
		~Game();
		bool sendMove(string, int);
		int addPlayer(Player*);
		int removePlayer(Player*);
		int gameID;
		int rdFD;
		int recentFD();
		bool exists(Player*);
		bool isFull();
		Player* getOwner();
		Player* getOpposite(Player*);
		Player** getPlayers();
	private:
		int pcount;
		Player *p1;
		Player *p2;
};
#endif
