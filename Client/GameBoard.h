#ifndef _GAMEBOARD_H
#define _GAMEBOARD_H
#include "User.h"

using namespace std;

class GameBoard {
	public:
		GameBoard(User*, User*);
		~GameBoard();
		string checkWinner();
		bool gameOver(string);	
		int update(int, User&);
		void draw();
		int getSpots();
		void reset();

	private:
		char* board;
		const static int count = 9;
		string winner;
		bool over;
		string last;
		int spotsLeft;
		User *player1;	
		User *player2;
};
#endif
