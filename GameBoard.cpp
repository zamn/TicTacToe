#include "GameBoard.h"

GameBoard::GameBoard(User* player1, User* player2) {
	this->player1 = player1;
	this->player2 = player2;
	spotsLeft = 9;
	board = new char[spotsLeft];
	for (int i = 0; i < 9; i++) {	
		board[i] = (char)(i+1);
	}
}

string GameBoard::checkWinner() {
	char prev;
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
	
}

int GameBoard::update(int p, User &u) {
	if (last == u.getNick()) {
		return 0;
	}
	else {
		if (board[p] != ' ') {
			return -1;
		}
		else {
			board[p] = u.getSymbol();
			cout << u.getNick() << " entered " << u.getSymbol() << " at postiion " << p << endl;
			spotsLeft--;
			if (spotsLeft == 0)
				return 2;
			draw();
			return 1;
		}
	}
}

void GameBoard::draw() {
	for (int i = 0; i < 9; i++) {
		if (i % 3 == 0) {
			cout << board[i] << endl;
			cout << "-- -- --" << endl;
		}
		else {
			cout << board[i] << " | ";
		}
	}
}

bool GameBoard::gameOver() {
	return over;
}
