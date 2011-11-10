#include <iostream>
#include "GameBoard.h"
#include "User.h"

using namespace std;

int main(void) {
	User *player1 = new User("adam", 'X');
	User *player2 = new User("Aaron", 'O');
	GameBoard gb(player1, player2);
	gb.draw();
}
