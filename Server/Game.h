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
		bool removePlayer(Player*);
		int gameID;
		bool exists(Player*);
		bool isFull();
		string getOwner();
		Player* getOpposite(Player*);
		Player** getPlayers();
	private:
		bool full;
		Player *p1;
		Player *p2;
};
#endif
