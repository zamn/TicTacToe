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

bool GameManager::addGame(Game* g) {
	if (tracker <= MAX_GAMES) {
		if (free->empty()) {
			cout << "tits?";
			games[tracker] = g;
			tracker++;
		}
		else {
			games[free->top()] = g;
			tracker++;
		}
	}
	else
		return false;
}

Game* GameManager::getGame(int n) {
	return games[n];
}
