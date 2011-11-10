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
		char board[];	
		const static int count = 9;
		string winner;
		bool over;
		string last;
		int spotsLeft = 9;
		User *player1;	
		User *player2;
};
