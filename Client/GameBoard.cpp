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
	// Diagonals!
	if ((board[0] == board[4]) && (board[0] == board[8]) && (board[8] == board[4])) {
		over = true;
		if (board[0] == player1->getSymbol()) 
			return player1->getNick();
		else 
			return player2->getNick();
	}
	else if ((board[2] == board[4]) && (board[2] == board[6]) && (board[4] == board[6])) {
		over = true;
		if (board[2] == player1->getSymbol())
			return player1->getNick();
		else
			return player2->getNick();
	}

	// checking in a row
	for (int i = 0; i < 7; i += 3) {
		if ((board[i] == board[i+1]) && (board[i] == board[i+2]) && (board[i+1] == board[i+2])) {
			over = true;
			if (board[i] == player1->getSymbol()) {
				return player1->getNick();
			}
			else {
				return player2->getNick();
			}
		}
	}

	// checking column matching
	for (int i = 0; i < 3; i++) {
		if ((board[i] == board[i+3]) && (board[i] == board[i+6]) && (board[i+3] == board[i+6])) {
			over = true;
			if (board[i] == player1->getSymbol()) {
				return player1->getNick();
			}
			else {
				return player2->getNick();
			}
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
			//cout << u.getNick() << " entered " << u.getSymbol() << " at postiion " << p << endl;
			spotsLeft--;
			if (spotsLeft == 0)
				return 2;
			last = u.getNick();
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
	last = "";
}
