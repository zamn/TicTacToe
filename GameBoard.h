#include <cppunit/extensions/HelperMacros.h>
#include "User.h"

using namespace std;

class GameBoard {
	public:
		GameBoard(*User, *User);
		string checkWinner();
		bool gameOver();	
		int update(int, int);
		void draw();

	private:
		char board[];	
		const static int count = 9;
		string winner;
		bool over;
		User *player1;	
		User *player2;
};
