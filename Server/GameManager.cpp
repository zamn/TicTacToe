#include <stack>
#include "Game.h"
#include "GameManager.h"

using namespace std;

GameManager::GameManager() {
	tracker = 0;
	free = new stack<int>();
}

bool GameManager::exists(int n) {
	if (games[n] != '\0') {
		return true;
	}
	return false;
}

int GameManager::addGame(Game* g) {
	cout << "MAX: " << MAX_GAMES << endl;
	cout << "TRACKER: " << tracker << endl;
	if (tracker <= MAX_GAMES) {
		if (free->empty()) {
			games[tracker] = g;
			tracker++;
			cout << "TRACKER: " << tracker << endl;
			return (tracker-1);
		}
		else {
			int spot = free->top();
			games[spot] = g;
			tracker++;
			return spot;
		}
	}
	else
		return -1;
}

Game* GameManager::getGame(int n) {
	return games[n];
}
