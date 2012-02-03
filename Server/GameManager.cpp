#include <stack>
#include "Game.h"
#include "GameManager.h"

using namespace std;

GameManager::GameManager() {
	tracker = 0;
}

bool GameManager::exists(int n) {
	return false;
}

bool GameManager::addGame(Game* g) {
	if (tracker <= MAX_GAMES) {
		if (free.empty()) {
			games[tracker] = g;
			tracker++;
		}
		else {
			games[free.top()] = g;
			tracker++;
		}
	}
	else
		return false;
}
