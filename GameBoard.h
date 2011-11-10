#include <cppunit/extensions/HelperMacros.h>
#include "User.h"

using namespace std;

class GameBoard {
	public:
		GameBoard(User*, User*);
		string checkWinner();
		bool gameOver();	
		int update(int, User&);
		void draw();

	private:
		char board[] = { '1', '2', '3', '4', '5', '6', '7', '8', '9' };	
		const static int count = 9;
		string winner;
		bool over;
		string last;
		int spotsLeft;
		User *player1;	
		User *player2;
};
