#include "GameBoard.h"

using namespace std;

GameBoard::GameBoard(User* player1, User* player2) {
	this->player1 = player1;
	this->player2 = player2;
	spotsLeft = 9;
	board = new char[spotsLeft];
	for (int i = 0; i < 9; i++) {	
		board[i] = (char)((int)'1'+i);
	}
}

GameBoard::~GameBoard() {
	delete board;
}

string GameBoard::checkWinner() {
	char prev = board[0];
	int cnt = 0;
	// Diagnols!
	if ((board[1] == board[5]) && (board[1] == board[9]) && (board[9] == board[5])) {
		over = true;
		if (board[1] == player1->getSymbol()) 
			return player1->getNick();
		else if (board[1] == player2->getSymbol())
			return player2->getNick();
	}
	else if ((board[3] == board[5]) && (board[3] == board[7]) && (board[5] == board[7])) {
		over = true;
		if (board[3] == player1->getSymbol())
			return player1->getNick();
		else if (board[3] == player2->getSymbol())
			return player2->getNick();
	}

	for (int i = 0; i < 10; i++) {
		if (board[i] == prev) {
			cnt++;
			if (cnt == 3) {
				over = true;
				if (board[i] == player1->getSymbol())
					return player1->getNick();
				else if (board[i] == player2->getSymbol())
					return player2->getNick();
			}
		}
		else {
			prev = board[i];
			cnt = 0;
		}
	}
	return "";	
}

/* GameBoard::update method returns serveral numbers
 * the return values mean the following:
 * -1 == spot taken! / invalid spot
 *  0 == not the Users turn
 *  1 == successfully updated
 *  2 == game over, no spots remaining!
 */

int GameBoard::update(int p, User &u) {
	if (last == u.getNick()) {
		return 0;
	}
	else {
		if (board[p-1] == player1->getSymbol() || board[p-1] == player2->getSymbol() || p > count) {
			return -1;
		}
		else {
			board[p-1] = u.getSymbol();
			cout << u.getNick() << " entered " << u.getSymbol() << " at postiion " << p << endl;
			spotsLeft--;
			if (spotsLeft == 0)
				return 2;
			last = u.getNick();
			draw();
			return 1;
		}
	}
}

void GameBoard::draw() {
	for (int i = 0; i < 9; i++) {
		if ((i+1) % 3 == 0) {
			cout << board[i] << endl;
			cout << "----------" << endl;
		}
		else {
			cout << board[i] << " | ";
		}
	}
}

int GameBoard::getSpots() {
	return spotsLeft;
}

bool GameBoard::gameOver(string player) {
	if (over) {
		cout << "Game over with " << player << " winning!" << endl;
		cout << "resetting board..." << endl;
		reset();
	}
	return over;
}

void GameBoard::reset() {
	for (int i = 0; i < count; i++) {
		board[i] = (char)((int)'1'+i);
	}
	spotsLeft = 9;
}
